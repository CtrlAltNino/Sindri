#include "TextureSettings/TextureSettings.hpp"
#include "pch.hpp"

#include "TextureBuffer.hpp"

namespace Sindri
{
  void
  TextureBuffer::Reserve(size_t width)
  {
    mWidth = width;
    mTextureDimension = TextureDimension::Texture1D;
    mData = std::vector<float>(mWidth);
  }

  void
  TextureBuffer::Reserve(size_t width, size_t height)
  {
    mWidth = width;
    mHeight = height;
    mTextureDimension = TextureDimension::Texture2D;
    mData = std::vector<float>(mWidth * mHeight);
  }

  void
  TextureBuffer::Reserve(size_t width, size_t height, size_t depth)
  {
    mWidth = width;
    mHeight = height;
    mDepth = depth;
    mTextureDimension = TextureDimension::Texture3D;
    mData = std::vector<float>(mWidth * mHeight * mDepth);
  }

  auto
  TextureBuffer::GetData() -> std::vector<float>&
  {
    return mData;
  }

  auto
  TextureBuffer::GetWidth() -> size_t
  {
    return mWidth;
  }

  auto
  TextureBuffer::GetHeight() -> size_t
  {
    return mHeight;
  }

  auto
  TextureBuffer::GetDepth() -> size_t
  {
    return mDepth;
  }

  auto
  TextureBuffer::GetDimension() -> TextureDimension
  {
    return mTextureDimension;
  }
}