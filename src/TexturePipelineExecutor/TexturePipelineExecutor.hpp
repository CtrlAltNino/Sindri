#pragma once

#include "IGpuPreviewTexture.hpp"
#include "ITextureBuffer.hpp"
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
    std::atomic<bool>        mCancelFlag = false;

    std::mutex               mWorkQueueMutex;
    std::queue<FillWorkload> mWorkQueue;
    size_t                   mCurrentNumWorkloads = 0;

    std::shared_ptr<ITexturePipeline>   mTexturePipeline = nullptr;
    std::shared_ptr<ITextureBuffer>     mTexture = nullptr;
    std::shared_ptr<IGpuPreviewTexture> mGpuPreviewTexture = nullptr;
    TextureSettings                     mCurrentTextureSettings;

    size_t                mThreadCount = 1;
    size_t                mWorkloadSize = 2048;
    std::atomic<uint32_t> mNumActiveWorkers{ 0 };

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
    TexturePipelineExecutor(
      std::shared_ptr<ITexturePipeline>   texturePipeline,
      std::shared_ptr<ITextureBuffer>     texture,
      std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture);

    ~TexturePipelineExecutor() override;

    void
    ExecutePipeline(TextureSettings settings) override;

    void
    CancelExecution() override;

    auto
    IsRunning() -> bool override;

    auto
    GetProgress() -> float override;
  };
}