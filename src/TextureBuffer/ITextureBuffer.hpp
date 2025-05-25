#pragma once

#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class ITextureBuffer
  {
  public:
    virtual ~ITextureBuffer() = default;

    virtual void
    Reserve(size_t width) = 0;

    virtual void
    Reserve(size_t width, size_t height) = 0;

    virtual void
    Reserve(size_t width, size_t height, size_t depth) = 0;

    virtual auto
    GetData() -> std::vector<float>& = 0;

    virtual auto
    GetTempData() -> std::vector<float>& = 0;

    virtual void
    PromoteTemp() = 0;

    virtual auto
    GetWidth() -> size_t = 0;

    virtual auto
    GetHeight() -> size_t = 0;

    virtual auto
    GetDepth() -> size_t = 0;

    virtual auto
    GetDimension() -> TextureDimension = 0;
  };
}