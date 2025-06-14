#include "pch.hpp"

#include "Helper/CoordinateHelper.hpp"
#include "NoiseLayer/INoiseLayer.hpp"
#include "TexturePipelineExecutor.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <optional>
#include <sol/protected_function_result.hpp>
#include <utility>

namespace Sindri
{
  TexturePipelineExecutor::TexturePipelineExecutor(
    std::shared_ptr<ITexturePipeline>   texturePipeline,
    std::shared_ptr<ITextureBuffer>     texture,
    std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture)
    : mTexturePipeline(std::move(texturePipeline))
    , mTexture(std::move(texture))
    , mThreadCount(std::max(1U, std::thread::hardware_concurrency() - 1))
    , mGpuPreviewTexture(std::move(gpuPreviewTexture))
  {
    for (int i = 0; i < mThreadCount; i++)
    {
      mThreadPool.emplace_back([this]() { TextureFiller(); });
    }
  }

  TexturePipelineExecutor::~TexturePipelineExecutor()
  {
    mStopThreadFlag.store(true);
    mCondition.notify_all();

    for (auto& thread : mThreadPool)
    {
      if (thread.joinable())
      {
        thread.join();
      }
    }
  }

  void
  TexturePipelineExecutor::TextureFiller()
  {
    while (!mStopThreadFlag.load())
    {
      {
        std::unique_lock<std::mutex> lock(mUploadMutex);
        mCondition.wait(
          lock,
          [this] { return !IsWorkloadQueueEmpty() || mStopThreadFlag.load(); });
      }

      if (!mStopThreadFlag.load())
      {
        // TODO: Create a lua worker state and initialize it
        std::vector<StackState> stack = InitializeState();

        std::vector<float>& data = mTexture->GetTempData();

        mNumActiveWorkers.fetch_add(1, std::memory_order_relaxed);
        while (auto workload = AcquireWorkload())
        {
          for (size_t i = workload->Offset;
               (i < data.size()) && (i < workload->Offset + workload->Length);
               i++)
          {
            float computed =
              EvaluateStack(stack,
                            IndexToCoord(i,
                                         mCurrentTextureSettings.Resolution,
                                         mCurrentTextureSettings.Dimensions));
            data[i] = computed;
          }

          if (mCancelFlag.load())
          {
            break;
          }
        }

        if (mCancelFlag.load())
        {
          std::unique_lock<std::mutex> lock(mWorkQueueMutex);
          mNumActiveWorkers.fetch_sub(1, std::memory_order_relaxed);
          mWorkQueue = {};
          mCurrentNumWorkloads = 0;
          if (mNumActiveWorkers.load() == 0)
          {
            mCancelFlag.store(false);
          }
        }
        else
        {
          mNumActiveWorkers.fetch_sub(1, std::memory_order_relaxed);

          if (mNumActiveWorkers.load() == 0)
          {
            mTexture->PromoteTemp();
            mGpuPreviewTexture->SetWaitingForUpload(true);
          }
        }
      }
    }
  }

  void
  TexturePipelineExecutor::ExecutePipeline(TextureSettings textureSettings)
  {
    mCurrentTextureSettings = textureSettings;

    // Chunking the work
    GenerateWorkloads();

    // Dispatching the worker threads
    mCondition.notify_all();
  }

  auto
  TexturePipelineExecutor::IsWorkloadQueueEmpty() -> bool
  {
    std::unique_lock<std::mutex> lock(mWorkQueueMutex);
    bool                         isEmpty = mWorkQueue.empty();

    return isEmpty;
  }

  auto
  TexturePipelineExecutor::AcquireWorkload() -> std::optional<FillWorkload>
  {
    std::unique_lock<std::mutex> lock(mWorkQueueMutex);

    if (mWorkQueue.empty())
    {
      return std::nullopt;
    }

    FillWorkload workLoad = mWorkQueue.front();
    mWorkQueue.pop();
    return workLoad;
  }

  void
  TexturePipelineExecutor::GenerateWorkloads()
  {
    size_t currentPos = 0;
    while (currentPos < mTexture->GetTempData().size())
    {
      FillWorkload newWorkload;
      newWorkload.Offset = currentPos;
      newWorkload.Length =
        (newWorkload.Offset + mWorkloadSize) < mTexture->GetTempData().size()
          ? mWorkloadSize
          : mTexture->GetTempData().size() - currentPos;

      currentPos += newWorkload.Length;

      mWorkQueue.push(newWorkload);
    }

    mCurrentNumWorkloads = mWorkQueue.size();
  }

  auto
  TexturePipelineExecutor::InitializeState() -> std::vector<StackState>
  {
    std::vector<StackState> stackState;

    for (auto& stackEntry : mTexturePipeline->GetLayers())
    {
      if (!stackEntry->IsEnabled())
      {
        continue;
      }
      StackState state;
      state.BlendMode = stackEntry->GetBlendMode();
      state.Contribution = stackEntry->GetContribution();

      // Load scripts
      state.LuaState.open_libraries(
        sol::lib::math, sol::lib::base, sol::lib::string);
      state.LuaState.script_file(stackEntry->GetPath().string());

      // Apply settings
      // TODO:

      for (auto& pair : stackEntry->GetSettings())
      {
        std::string                    key = pair.first;
        std::variant<bool, int, float> value = pair.second;

        if (std::holds_alternative<int>(value))
        {
          state.LuaState["Settings"][key] = std::get<int>(value);
        }
        else if (std::holds_alternative<float>(value))
        {
          state.LuaState["Settings"][key] = std::get<float>(value);
        }
        else if (std::holds_alternative<bool>(value))
        {
          state.LuaState["Settings"][key] = std::get<bool>(value);
        }
      }

      if (state.LuaState["Setup"].valid())
      {
        state.LuaState["Setup"](mCurrentTextureSettings.Seed);
      }

      stackState.push_back(std::move(state));
    }

    return stackState;
  }

  auto
  TexturePipelineExecutor::EvaluateStack(std::vector<StackState>& stack,
                                         glm::ivec3 coordinate) -> float
  {
    float value = 0.0F;

    for (auto& stackState : stack)
    {
      float normalizedX =
        (float)coordinate.x / (float)mCurrentTextureSettings.Resolution.x;
      float normalizedY =
        (float)coordinate.y / (float)mCurrentTextureSettings.Resolution.y;
      float normalizedZ =
        (float)coordinate.z / (float)mCurrentTextureSettings.Resolution.z;

      // sol::protected_function_result result =
      //   mEvaluate(normalizedX, normalizedY, normalizedZ, settings->mSeed);
      float result = 0.0F;

      sol::protected_function_result functionResult;

      if (mCurrentTextureSettings.Dimensions == TextureDimension::Texture2D)
      {
        functionResult = stackState.LuaState["Evaluate2D"](
          normalizedX, normalizedY, mCurrentTextureSettings.Seed);
      }
      else if (mCurrentTextureSettings.Dimensions ==
               TextureDimension::Texture3D)
      {
        functionResult = stackState.LuaState["Evaluate3D"](
          normalizedX, normalizedY, normalizedZ, mCurrentTextureSettings.Seed);
      }

      if (!functionResult.valid())
      {
        sol::error err = functionResult;
        std::cerr << "Lua error: " << err.what() << std::endl;
      }
      else
      {
        result =
          functionResult.get<float>(); // or result.get<float>() for safety
      }

      result *= stackState.Contribution;

      switch (stackState.BlendMode)
      {
        case Add:
          {
            value += result;
          }
          break;
        case Multiply:
          {
            value *= result;
          }
          break;
      }
    }

    return value;
  }

  void
  TexturePipelineExecutor::CancelExecution()
  {
    mCancelFlag.store(true);
  }

  auto
  TexturePipelineExecutor::IsRunning() -> bool
  {
    return mNumActiveWorkers.load() > 0;
  }

  auto
  TexturePipelineExecutor::GetProgress() -> float
  {
    return (float)(mCurrentNumWorkloads - mWorkQueue.size()) /
           (float)mCurrentNumWorkloads;
  }
}