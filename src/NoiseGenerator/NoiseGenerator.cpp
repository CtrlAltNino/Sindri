#include "StackEntry.hpp"
#include "pch.hpp"

#include "NoiseGenerator.hpp"
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

      if (!mStopThreadFlag.load())
      {
        // TODO: Create a lua worker state and initialize it
        std::vector<StackState> stack = InitializeState();

        std::vector<float>& data = mTexture->GetData();

        while (auto workload = AcquireWorkload())
        {
          for (size_t i = workload->Offset;
               (i < data.size()) && (i < workload->Offset + workload->Length);
               i++)
          {
            // TODO: Update to using the thread local lua state
            /*data[i] = mCompositionStack->Evaluate(
              mTextureSettings,
              IndexToCoord(i,
                           mTextureSettings->mResolution,
                           mTextureSettings->mDimensions));*/
            data[i] =
              EvaluateStack(stack,
                            IndexToCoord(i,
                                         mTextureSettings->mResolution,
                                         mTextureSettings->mDimensions));
          }

          mTexture->SetWaitingForUpload(true);
        }
      }
    }
  }

  void
  NoiseGenerator::RequestTextureFill()
  {
    // Serializing the current state so it can be copied to the worker threads
    for (auto& stackEntry : mCompositionStack->GetEntries())
    {
      stackEntry.Serialize();
    }

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
      newWorkload.Offset = 0;
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
    }
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