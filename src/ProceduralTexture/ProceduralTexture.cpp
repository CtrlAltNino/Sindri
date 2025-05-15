#include "pch.hpp"

#include "ProceduralTexture.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  void
  ProceduralTexture::Upload()
  {
    if (mTextureId != 0)
    {
      glDeleteTextures(1, &mTextureId);
    }

    glGenTextures(1, &mTextureId);

    GLenum target = 0;
    GLint  internalFormat = 0;
    GLenum glFormat = GL_RED; // single channel
    GLenum glType = 0;

    switch (mTextureDimension)
    {
      case TextureDimension::Texture1D: target = GL_TEXTURE_1D; break;
      case TextureDimension::Texture2D: target = GL_TEXTURE_2D; break;
      case TextureDimension::Texture3D: target = GL_TEXTURE_3D; break;
      default: glDeleteTextures(1, &mTextureId); return;
    }

    switch (mTextureFormat)
    {
      case TextureFormat::U8:
        internalFormat = GL_R8;
        glType = GL_UNSIGNED_BYTE;
        break;
      case TextureFormat::F32:
        internalFormat = GL_R32F;
        glType = GL_FLOAT;
        break;
      default: glDeleteTextures(1, &mTextureId); return;
    }

    glBindTexture(target, mTextureId);
    GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

    // Set default parameters, can customize
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    if (mTextureDimension != TextureDimension::Texture1D)
      glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (mTextureDimension == TextureDimension::Texture3D)
      glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Upload data based on dimension and format
    if (mTextureDimension == TextureDimension::Texture1D)
    {
      if (mTextureFormat == TextureFormat::U8)
      {
        glTexImage1D(target,
                     0,
                     internalFormat,
                     mWidth,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<unsigned char>>(mData).data());
      }
      else
      {
        glTexImage1D(target,
                     0,
                     internalFormat,
                     mWidth,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<float>>(mData).data());
      }
    }
    else if (mTextureDimension == TextureDimension::Texture2D)
    {
      if (mTextureFormat == TextureFormat::U8)
      {
        glTexImage2D(target,
                     0,
                     internalFormat,
                     mWidth,
                     mHeight,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<unsigned char>>(mData).data());
      }
      else
      {
        glTexImage2D(target,
                     0,
                     internalFormat,
                     mWidth,
                     mHeight,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<float>>(mData).data());
      }
    }
    else if (mTextureDimension == TextureDimension::Texture3D)
    {
      if (mTextureFormat == TextureFormat::U8)
      {
        glTexImage3D(target,
                     0,
                     internalFormat,
                     mWidth,
                     mHeight,
                     mDepth,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<unsigned char>>(mData).data());
      }
      else
      {
        glTexImage3D(target,
                     0,
                     internalFormat,
                     mWidth,
                     mHeight,
                     mDepth,
                     0,
                     glFormat,
                     glType,
                     std::get<std::vector<float>>(mData).data());
      }
    }

    glBindTexture(target, 0);

    mIsUploaded = true;
  }
}