#include "pch.hpp"

#include "ProceduralTexture.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  void
  ProceduralTexture::Reserve(size_t width)
  {
    mWidth = width;
    mTextureDimension = TextureDimension::Texture1D;
    mData = std::vector<float>(mWidth);
  }

  void
  ProceduralTexture::Reserve(size_t width, size_t height)
  {
    mWidth = width;
    mHeight = height;
    mTextureDimension = TextureDimension::Texture2D;
    mData = std::vector<float>(mWidth * mHeight);
  }

  void
  ProceduralTexture::Reserve(size_t width, size_t height, size_t depth)
  {
    mWidth = width;
    mHeight = height;
    mDepth = depth;
    mTextureDimension = TextureDimension::Texture3D;
    mData = std::vector<float>(mWidth * mHeight * mDepth);
  }

  void
  ProceduralTexture::Upload()
  {
    std::cout << "Uploading texture" << std::endl;
    if (mTextureId != 0)
    {
      glDeleteTextures(1, &mTextureId);
    }

    /*for (int i = 0; i < mData.size(); i++)
    {
      std::cout << "pixel data at position " << i << ": " << mData[i]
                << std::endl;
    }*/

    GLenum target = 0;
    GLint  internalFormat = GL_R32F;
    GLenum glFormat = GL_RED; // single channel
    GLenum glType = GL_FLOAT;

    switch (mTextureDimension)
    {
      case TextureDimension::Texture1D: target = GL_TEXTURE_1D; break;
      case TextureDimension::Texture2D: target = GL_TEXTURE_2D; break;
      case TextureDimension::Texture3D: target = GL_TEXTURE_3D; break;
    }

    glCreateTextures(target, 1, &mTextureId);

    // glBindTexture(target, mTextureId);
    GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTextureParameteriv(mTextureId, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

    // Set default parameters, can customize
    UpdateTextureFiltering();
    glTextureParameteri(mTextureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    if (mTextureDimension != TextureDimension::Texture1D)
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    if (mTextureDimension == TextureDimension::Texture3D)
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    // Upload data based on dimension and format
    if (mTextureDimension == TextureDimension::Texture1D)
    {
      glTextureStorage1D(mTextureId, 1, internalFormat, mWidth);
      glTextureSubImage1D(
        mTextureId, 0, 0, mWidth, glFormat, glType, mData.data());
    }
    else if (mTextureDimension == TextureDimension::Texture2D)
    {
      glTextureStorage2D(mTextureId, 1, internalFormat, mWidth, mHeight);
      glTextureSubImage2D(
        mTextureId, 0, 0, 0, mWidth, mHeight, glFormat, glType, mData.data());
    }
    else if (mTextureDimension == TextureDimension::Texture3D)
    {
      glTextureStorage3D(
        mTextureId, 1, internalFormat, mWidth, mHeight, mDepth);
      glTextureSubImage3D(mTextureId,
                          0,
                          0,
                          0,
                          0,
                          mWidth,
                          mHeight,
                          mDepth,
                          glFormat,
                          glType,
                          mData.data());
    }

    mIsUploaded = true;
    SetWaitingForUpload(false);
    std::cout << "Texture upload complete" << std::endl;
  }

  auto
  ProceduralTexture::GetInterpolatePreview() const -> bool
  {
    return mInterpolate;
  }

  void
  ProceduralTexture::SetInterpolatePreview(bool interpolate)
  {
    mInterpolate = interpolate;

    if (mIsUploaded)
    {
      UpdateTextureFiltering();
    }
  }

  void
  ProceduralTexture::UpdateTextureFiltering() const
  {

    if (mInterpolate)
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(mTextureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTextureParameteri(mTextureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
  }

  auto
  ProceduralTexture::GetWaitingForUpload() const -> bool
  {
    return mWaitingForUpload.load();
  }

  void
  ProceduralTexture::SetWaitingForUpload(bool waitingForUpload)
  {
    mWaitingForUpload.store(waitingForUpload);
  }
}