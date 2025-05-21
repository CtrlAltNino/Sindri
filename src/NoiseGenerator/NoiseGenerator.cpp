#include "pch.hpp"

#include "NoiseGenerator.hpp"
#include "StackEntry.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include "Utility/CoordinateHelper.hpp"
#include <optional>
#include <random>
#include <sol/protected_function_result.hpp>
#include <utility>

namespace Sindri
{
  NoiseGenerator::NoiseGenerator(
    std::shared_ptr<CompositionStack>  compositionStack,
    std::shared_ptr<TextureSettings>   settings,
    std::shared_ptr<ProceduralTexture> texture)
    : mCompositionStack(std::move(compositionStack))
    , mTextureSettings(std::move(settings))
    , mTexture(std::move(texture))
    , mThreadCount(std::thread::hardware_concurrency())
  {
    // mUploadThread = std::thread([this]() { TextureFiller(); });
    for (int i = 0; i < mThreadCount; i++)
    {
      mThreadPool.emplace_back([this]() { TextureFiller(); });
    }
  }

  NoiseGenerator::~NoiseGenerator()
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
  NoiseGenerator::TextureFiller()
  {
    while (!mStopThreadFlag.load())
    {
      {
        std::unique_lock<std::mutex> lock(mUploadMutex);
        mCondition.wait(
          lock,
          [this] { return !IsWorkloadQueueEmpty() || mStopThreadFlag.load(); });
      }

      std::cout << "Worker thread woken up" << std::endl;

      if (!mStopThreadFlag.load())
      {
        std::cout << "Initializing worker thread" << std::endl;
        // TODO: Create a lua worker state and initialize it
        std::vector<StackState> stack = InitializeState();

        std::cout << "Getting data target" << std::endl;
        std::vector<float>& data = mTexture->GetData();

        std::cout << "Work queue processing" << std::endl;
        while (auto workload = AcquireWorkload())
        {
          bool lastOne = IsWorkloadQueueEmpty();
          for (size_t i = workload->Offset;
               (i < data.size()) && (i < workload->Offset + workload->Length);
               i++)
          {
            float computed =
              EvaluateStack(stack,
                            IndexToCoord(i,
                                         mTextureSettings->mResolution,
                                         mTextureSettings->mDimensions));
            data[i] = computed;
            // std::cout << "Computed pixel value: " << computed << std::endl;
          }

          if (lastOne)
          {
            mTexture->SetWaitingForUpload(true);
          }
        }
        std::cout << "Work queue empty" << std::endl;
      }
    }
  }

  void
  NoiseGenerator::RequestTextureFill()
  {
    // Chunking the work
    GenerateWorkloads();

    // Dispatching the worker threads
    mCondition.notify_all();
  }

  auto
  NoiseGenerator::IsWorkloadQueueEmpty() -> bool
  {
    std::unique_lock<std::mutex> lock(mWorkQueueMutex);
    bool                         isEmpty = mWorkQueue.empty();

    return isEmpty;
  }

  auto
  NoiseGenerator::AcquireWorkload() -> std::optional<FillWorkload>
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
  NoiseGenerator::GenerateWorkloads()
  {
    size_t currentPos = 0;
    while (currentPos < mTexture->GetData().size())
    {
      FillWorkload newWorkload;
      newWorkload.Offset = currentPos;
      newWorkload.Length =
        (newWorkload.Offset + mWorkloadSize) < mTexture->GetData().size()
          ? mWorkloadSize
          : mTexture->GetData().size() - currentPos;

      currentPos += newWorkload.Length;

      mWorkQueue.push(newWorkload);
    }
  }

  auto
  NoiseGenerator::InitializeState() -> std::vector<StackState>
  {
    std::vector<StackState> stackState;

    for (auto& stackEntry : mCompositionStack->GetEntries())
    {
      StackState state;
      state.Type = stackEntry.GetComposeType();

      // Load scripts
      state.State.open_libraries(
        sol::lib::math, sol::lib::base, sol::lib::string);
      state.State.script_file(stackEntry.GetPath().string());

      // Apply settings
      // TODO:

      for (auto& pair : stackEntry.GetSettings())
      {
        std::string                    key = pair.first;
        std::variant<bool, int, float> value = pair.second;

        if (std::holds_alternative<int>(value))
        {
          state.State["settings"][key] = std::get<int>(value);
        }
        else if (std::holds_alternative<float>(value))
        {
          state.State["settings"][key] = std::get<float>(value);
        }
        else if (std::holds_alternative<bool>(value))
        {
          state.State["settings"][key] = std::get<bool>(value);
        }
      }

      stackState.push_back(std::move(state));
    }

    return stackState;
  }

  auto
  NoiseGenerator::EvaluateStack(std::vector<StackState>& stack,
                                glm::ivec3               coordinate) -> float
  {
    float value = 0.0F;

    for (auto& stackState : stack)
    {
      float normalizedX =
        (float)coordinate.x / (float)mTextureSettings->mResolution.x;
      float normalizedY =
        (float)coordinate.y / (float)mTextureSettings->mResolution.y;
      float normalizedZ =
        (float)coordinate.z / (float)mTextureSettings->mResolution.z;

      // sol::protected_function_result result =
      //   mEvaluate(normalizedX, normalizedY, normalizedZ, settings->mSeed);
      float                          result = 0.0F;
      sol::protected_function_result functionResult =
        stackState.State["evaluate"](
          normalizedX, normalizedY, normalizedZ, mTextureSettings->mSeed);

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

      switch (stackState.Type)
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
}