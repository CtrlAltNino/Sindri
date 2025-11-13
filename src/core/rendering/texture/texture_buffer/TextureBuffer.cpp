#include "pch.hpp"

#include "TextureBuffer.hpp"
#include "WorkflowSettings.hpp"

namespace Sindri
{
  void
  TextureBuffer::Reserve(size_t width, size_t channels)
  {
    mTempWidth = width;
    mTempChannels = channels;
    mTextureDimension = TextureDimension::Texture1D;
    mTempData = std::vector<float>(mTempWidth * mTempChannels);
  }

  void
  TextureBuffer::Reserve(size_t width, size_t height, size_t channels)
  {
    mTempWidth = width;
    mTempHeight = height;
    mTempChannels = channels;
    mTextureDimension = TextureDimension::Texture2D;
    mTempData = std::vector<float>(mTempWidth * mTempHeight * mTempChannels);
  }

  void
  TextureBuffer::Reserve(size_t width,
                         size_t height,
                         size_t depth,
                         size_t channels)
  {
    mTempWidth = width;
    mTempHeight = height;
    mTempDepth = depth;
    mTempChannels = channels;
    mTextureDimension = TextureDimension::Texture3D;
    mTempData =
      std::vector<float>(mTempWidth * mTempHeight * mTempDepth * mTempChannels);
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
    mChannels = mTempChannels;
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
  TextureBuffer::GetChannels() -> size_t
  {
    return mChannels;
  }

  auto
  TextureBuffer::GetDimension() -> TextureDimension
  {
    return mTextureDimension;
  }
}