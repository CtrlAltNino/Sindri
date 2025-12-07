#include "pch.hpp"

#include "GpuPreviewTextureFactory.hpp"

#if defined(__APPLE__)
#include "MetalPreviewTexture.hpp"
#endif

#if defined(_WIN32) || (__linux__)
#include "OpenGLPreviewTexture.hpp"
#endif

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
#if defined(__APPLE__)
    return std::make_unique<MetalPreviewTexture>(
      mTextureBufferFactory->Create());
#elif defined(_WIN32) || defined(__linux__)
    return std::make_unique<OpenGLPreviewTexture>(
      mTextureBufferFactory->Create());
#endif
  }
}