#include "pch.hpp"

#include "OpenGLPreviewTexture.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <glad/glad.h>

namespace Sindri
{
  OpenGLPreviewTexture::OpenGLPreviewTexture(
    std::shared_ptr<ITextureBuffer> textureBuffer)
    : mTextureBuffer(std::move(textureBuffer))
  {
  }

  void
  OpenGLPreviewTexture::Upload()
  {
    std::cout << "Uploading texture" << std::endl;
    if (mTextureId != 0)
    {
      glDeleteTextures(1, &mTextureId);
    }

    GLenum target = 0;
    GLint  internalFormat = GL_R32F;
    GLenum glFormat = GL_RED; // single channel
    GLenum glType = GL_FLOAT;

    switch (mTextureBuffer->GetDimension())
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

    if (mTextureBuffer->GetDimension() != TextureDimension::Texture1D)
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    if (mTextureBuffer->GetDimension() == TextureDimension::Texture3D)
    {
      glTextureParameteri(mTextureId, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    // Upload data based on dimension and format
    if (mTextureBuffer->GetDimension() == TextureDimension::Texture1D)
    {
      glTextureStorage1D(
        mTextureId, 1, internalFormat, mTextureBuffer->GetWidth());
      glTextureSubImage1D(mTextureId,
                          0,
                          0,
                          mTextureBuffer->GetWidth(),
                          glFormat,
                          glType,
                          mTextureBuffer->GetData().data());
    }
    else if (mTextureBuffer->GetDimension() == TextureDimension::Texture2D)
    {
      glTextureStorage2D(mTextureId,
                         1,
                         internalFormat,
                         mTextureBuffer->GetWidth(),
                         mTextureBuffer->GetHeight());
      glTextureSubImage2D(mTextureId,
                          0,
                          0,
                          0,
                          mTextureBuffer->GetWidth(),
                          mTextureBuffer->GetHeight(),
                          glFormat,
                          glType,
                          mTextureBuffer->GetData().data());
    }
    else if (mTextureBuffer->GetDimension() == TextureDimension::Texture3D)
    {
      glTextureStorage3D(mTextureId,
                         1,
                         internalFormat,
                         mTextureBuffer->GetWidth(),
                         mTextureBuffer->GetHeight(),
                         mTextureBuffer->GetDepth());
      glTextureSubImage3D(mTextureId,
                          0,
                          0,
                          0,
                          0,
                          mTextureBuffer->GetWidth(),
                          mTextureBuffer->GetHeight(),
                          mTextureBuffer->GetDepth(),
                          glFormat,
                          glType,
                          mTextureBuffer->GetData().data());
    }

    mIsUploaded = true;
    SetWaitingForUpload(false);
    std::cout << "Texture upload complete" << std::endl;
  }

  auto
  OpenGLPreviewTexture::GetInterpolatePreview() const -> bool
  {
    return mInterpolate;
  }

  void
  OpenGLPreviewTexture::SetInterpolatePreview(bool interpolate)
  {
    mInterpolate = interpolate;

    if (mIsUploaded)
    {
      UpdateTextureFiltering();
    }
  }

  void
  OpenGLPreviewTexture::UpdateTextureFiltering() const
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
  OpenGLPreviewTexture::GetWaitingForUpload() const -> bool
  {
    return mWaitingForUpload.load();
  }

  void
  OpenGLPreviewTexture::SetWaitingForUpload(bool waitingForUpload)
  {
    mWaitingForUpload.store(waitingForUpload);
  }
}