#include "pch.hpp"

#include "TextureBuffer.hpp"
#include "TextureSettings/TextureSettings.hpp"

namespace Sindri
{
  void
  TextureBuffer::Reserve(size_t width)
  {
    mTempWidth = width;
    mTextureDimension = TextureDimension::Texture1D;
    mTempData = std::vector<float>(mTempWidth);
  }

  void
  TextureBuffer::Reserve(size_t width, size_t height)
  {
    mTempWidth = width;
    mTempHeight = height;
    mTextureDimension = TextureDimension::Texture2D;
    mTempData = std::vector<float>(mTempWidth * mTempHeight);
  }

  void
  TextureBuffer::Reserve(size_t width, size_t height, size_t depth)
  {
    mTempWidth = width;
    mTempHeight = height;
    mTempDepth = depth;
    mTextureDimension = TextureDimension::Texture3D;
    mTempData = std::vector<float>(mTempWidth * mTempHeight * mTempDepth);
  }

  auto
  TextureBuffer::GetData() -> std::vector<float>&
  {
    return mData;
  }

  auto
  TextureBuffer::GetTempData() -> std::vector<float>&
  {
    return mTempData;
  }

  void
  TextureBuffer::PromoteTemp()
  {
    mWidth = mTempWidth;
    mHeight = mTempHeight;
    mDepth = mTempDepth;
    mData = mTempData;
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