#pragma once

#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class ProceduralTexture
  {
  private:
    TextureDimension   mTextureDimension;
    size_t             mWidth = 0;
    size_t             mHeight = 0;
    size_t             mDepth = 0;
    std::atomic<bool>  mWaitingForUpload = false;
    bool               mIsUploaded = false;
    std::vector<float> mData;
    GLuint             mTextureId = 0;
    bool               mInterpolate = true;

    void
    UpdateTextureFiltering() const;

  public:
    ProceduralTexture() = default;

    void
    Reserve(size_t width);

    void
    Reserve(size_t width, size_t height);

    void
    Reserve(size_t width, size_t height, size_t depth);

    auto
    GetData() -> std::vector<float>&
    {
      return mData;
    }

    void
    Upload();

    [[nodiscard]]
    auto
    GetTextureId() const -> uintptr_t
    {
      return mTextureId;
    }

    [[nodiscard]]
    auto
    GetIsUploaded() const -> bool
    {
      return mIsUploaded;
    }

    [[nodiscard]] auto
    GetInterpolatePreview() const -> bool;

    void
    SetInterpolatePreview(bool interpolate);

    [[nodiscard]] auto
    GetWaitingForUpload() const -> bool;

    void
    SetWaitingForUpload(bool waitingForUpload);
  };
}