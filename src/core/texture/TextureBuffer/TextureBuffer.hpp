#pragma once

#include "ITextureBuffer.hpp"
#include "TextureTypes.hpp"
#include "WorkflowSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class TextureBuffer : public ITextureBuffer
  {
  private:
    TextureDimension mTextureDimension = TextureDimension::Texture2D;

    std::vector<float> mData;
    size_t             mWidth = 0;
    size_t             mHeight = 0;
    size_t             mDepth = 0;
    size_t             mChannels = 1;

    std::vector<float> mTempData;
    size_t             mTempWidth = 0;
    size_t             mTempHeight = 0;
    size_t             mTempDepth = 0;
    size_t             mTempChannels = 1;

  public:
    TextureBuffer() = default;
    ~TextureBuffer() override = default;

    void
    Reserve(size_t width, size_t channels) override;

    void
    Reserve(size_t width, size_t height, size_t channels) override;

    void
    Reserve(size_t width,
            size_t height,
            size_t depth,
            size_t channels) override;

    auto
    GetData() -> std::vector<float>& override;

    auto
    GetTempData() -> std::vector<float>& override;

    void
    PromoteTemp() override;

    auto
    GetWidth() -> size_t override;

    auto
    GetHeight() -> size_t override;

    auto
    GetDepth() -> size_t override;

    auto
    GetChannels() -> size_t override;

    auto
    GetDimension() -> TextureDimension override;
  };
}