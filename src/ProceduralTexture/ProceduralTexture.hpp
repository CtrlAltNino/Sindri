#pragma once

#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  class ProceduralTexture
  {
  public:
    ProceduralTexture(TextureFormat textureFormat, size_t width)
      : mWidth(width)
      , mTextureFormat(textureFormat)
      , mTextureDimension(TextureDimension::Texture1D)
    {
      size_t count = width;
      switch (mTextureFormat)
      {
        case TextureFormat::U8:
          mData = std::vector<unsigned char>(count);
          break;
        case TextureFormat::F32: mData = std::vector<float>(count); break;
      }
    }

    ProceduralTexture(TextureFormat textureFormat, size_t width, size_t height)
      : mWidth(width)
      , mHeight(height)
      , mTextureFormat(textureFormat)
      , mTextureDimension(TextureDimension::Texture2D)
    {
      size_t count = width * height;
      switch (mTextureFormat)
      {
        case TextureFormat::U8:
          mData = std::vector<unsigned char>(count);
          break;
        case TextureFormat::F32: mData = std::vector<float>(count); break;
      }
    }

    ProceduralTexture(TextureFormat textureFormat,
                      size_t        width,
                      size_t        height,
                      size_t        depth)
      : mWidth(width)
      , mHeight(height)
      , mTextureFormat(textureFormat)
      , mTextureDimension(TextureDimension::Texture3D)
    {
      size_t count = width * height;
      switch (mTextureFormat)
      {
        case TextureFormat::U8:
          mData = std::vector<unsigned char>(count);
          break;
        case TextureFormat::F32: mData = std::vector<float>(count); break;
      }
    }

    template<typename T>
    auto
    GetTypedData() -> std::vector<T>&
    {
      return std::get<std::vector<T>>(mData);
    }

    [[nodiscard]] auto
    GetFormat() const -> TextureFormat
    {
      return mTextureFormat;
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

  private:
    TextureFormat    mTextureFormat;
    TextureDimension mTextureDimension;
    size_t           mWidth = 0;
    size_t           mHeight = 0;
    size_t           mDepth = 0;
    bool             mIsUploaded = false;
    std::variant<std::vector<unsigned char>, std::vector<float>> mData;
    GLuint                                                       mTextureId = 0;
  };
}