#pragma once

#include "ProceduralTexture.hpp"
#include "TexturePipeline/ITexturePipeline.hpp"
#include "TexturePipelineExecutor/ITexturePipelineExecutor.hpp"
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
    sol::state LuaState;
    BlendMode  BlendMode;
  };

  class TexturePipelineExecutor : public ITexturePipelineExecutor
  {
  private:
    std::vector<std::thread> mThreadPool;
    std::mutex               mUploadMutex;
    std::condition_variable  mCondition;
    std::atomic<bool>        mStopThreadFlag = false;

    std::mutex               mWorkQueueMutex;
    std::queue<FillWorkload> mWorkQueue;

    std::shared_ptr<ITexturePipeline>  mTexturePipeline = nullptr;
    std::shared_ptr<ProceduralTexture> mTexture = nullptr;
    TextureSettings                    mCurrentTextureSettings;

    size_t mThreadCount = 1;
    size_t mWorkloadSize = 2048;

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
    TexturePipelineExecutor(std::shared_ptr<ITexturePipeline>  texturePipeline,
                            std::shared_ptr<ProceduralTexture> texture);

    ~TexturePipelineExecutor() override;

    void
    ExecutePipeline(TextureSettings settings) override;
  };
}