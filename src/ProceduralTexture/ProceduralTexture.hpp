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
    bool               mIsUploaded = false;
    std::vector<float> mData;
    GLuint             mTextureId = 0;

  public:
    ProceduralTexture(size_t width)
      : mWidth(width)
      , mTextureDimension(TextureDimension::Texture1D)
    {
      size_t count = width;
      mData = std::vector<float>(count);
    }

    ProceduralTexture(size_t width, size_t height)
      : mWidth(width)
      , mHeight(height)
      , mTextureDimension(TextureDimension::Texture2D)
    {
      size_t count = width * height;
      mData = std::vector<float>(count);
    }

    ProceduralTexture(size_t width, size_t height, size_t depth)
      : mWidth(width)
      , mHeight(height)
      , mTextureDimension(TextureDimension::Texture3D)
    {
      size_t count = width * height;
      mData = std::vector<float>(count);
    }

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
  };
}