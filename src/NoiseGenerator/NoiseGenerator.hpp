#pragma once

#include "CompositionStack.hpp"
#include "ProceduralTexture.hpp"
#include "StackEntry.hpp"
#include <queue>

namespace Sindri
{
  struct FillWorkload
  {
    size_t Offset = 0;
    size_t Length = 0;
  };

  struct StackState
  {
    sol::state  State;
    ComposeType Type;
  };

  class NoiseGenerator
  {
  private:
    std::vector<std::thread> mThreadPool;
    std::mutex               mUploadMutex;
    std::condition_variable  mCondition;
    std::atomic<bool>        mStopThreadFlag = false;

    std::mutex               mWorkQueueMutex;
    std::queue<FillWorkload> mWorkQueue;

    std::shared_ptr<CompositionStack>  mCompositionStack = nullptr;
    std::shared_ptr<TextureSettings>   mTextureSettings = nullptr;
    std::shared_ptr<ProceduralTexture> mTexture = nullptr;

    size_t mThreadCount = 1;
    size_t mWorkloadSize = 512;

    void
    TextureFiller();

    auto
    IsWorkloadQueueEmpty() -> bool;

    auto
    AcquireWorkload() -> std::optional<FillWorkload>;

    auto
    InitializeState() -> std::vector<StackState>;

    void
    GenerateWorkloads();

    auto
    EvaluateStack(std::vector<StackState>& stack, glm::ivec3 coordinate)
      -> float;

  public:
    NoiseGenerator(std::shared_ptr<CompositionStack>  compositionStack,
                   std::shared_ptr<TextureSettings>   settings,
                   std::shared_ptr<ProceduralTexture> texture);

    ~NoiseGenerator();

    void
    RequestTextureFill();
  };
}