#include "OpenGLPreviewTexture.hpp"
#include "pch.hpp"

#include "GpuPreviewTextureFactory.hpp"

namespace Sindri
{
  GpuPreviewTextureFactory::GpuPreviewTextureFactory(
    std::shared_ptr<ITextureBufferFactory> textureBufferFactory)
    : mTextureBufferFactory(std::move(textureBufferFactory))
  {
  }

  auto
  GpuPreviewTextureFactory::Create() -> std::shared_ptr<IGpuPreviewTexture>
  {
    return std::make_shared<OpenGLPreviewTexture>(
      mTextureBufferFactory->Create());
  }
}