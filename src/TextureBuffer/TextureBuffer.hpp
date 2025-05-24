#pragma once

#include "TextureBuffer/ITextureBuffer.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class TextureBuffer : public ITextureBuffer
  {
  private:
    TextureDimension   mTextureDimension;
    size_t             mWidth = 0;
    size_t             mHeight = 0;
    size_t             mDepth = 0;
    std::vector<float> mData;

  public:
    TextureBuffer() = default;
    ~TextureBuffer() override = default;

    void
    Reserve(size_t width) override;

    void
    Reserve(size_t width, size_t height) override;

    void
    Reserve(size_t width, size_t height, size_t depth) override;

    auto
    GetData() -> std::vector<float>& override;

    auto
    GetWidth() -> size_t override;

    auto
    GetHeight() -> size_t override;

    auto
    GetDepth() -> size_t override;

    auto
    GetDimension() -> TextureDimension override;
  };
}