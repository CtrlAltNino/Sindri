#include "pch.hpp"

#include "NoiseGenerator.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include "Utility/CoordinateHelper.hpp"
#include <optional>
#include <random>
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
        std::vector stack = InitializeState();

        std::vector<float>& data = mTexture->GetData();

        while (auto workload = AcquireWorkload())
        {
          for (size_t i = workload->Offset;
               (i < data.size()) && (i < workload->Offset + workload->Length);
               i++)
          {
            // TODO: Update to using the thread local lua state
            data[i] = mCompositionStack->Evaluate(
              mTextureSettings,
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
    GenerateWorkloads();
    mCondition.notify_one();
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
    // TODO: Derive workloads
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
    // Load scripts

    // Apply settings
  }

  auto
  NoiseGenerator::EvaluateStack() -> float
  {
  }
}