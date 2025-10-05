#pragma once

#include "IGpuPreviewTexture.hpp"
#include "ITextureBuffer.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class OpenGLPreviewTexture : public IGpuPreviewTexture
  {
  private:
    std::atomic<bool>               mWaitingForUpload = false;
    bool                            mIsUploaded = false;
    GLuint                          mTextureId = 0;
    bool                            mInterpolate = true;
    std::shared_ptr<ITextureBuffer> mTextureBuffer;

    void
    UpdateTextureFiltering() const;

  public:
    OpenGLPreviewTexture(std::shared_ptr<ITextureBuffer> textureBuffer);
    ~OpenGLPreviewTexture() override;

    void
    Upload() override;

    [[nodiscard]]
    auto
    GetTextureId() const -> uintptr_t override;

    [[nodiscard]]
    auto
    GetIsUploaded() const -> bool override;

    [[nodiscard]] auto
    GetInterpolatePreview() const -> bool override;

    void
    SetInterpolatePreview(bool interpolate) override;

    [[nodiscard]] auto
    GetWaitingForUpload() const -> bool override;

    void
    SetWaitingForUpload(bool waitingForUpload) override;
  };
}