#pragma once

#include "IGpuPreviewTextureFactory.hpp"
#include "ITextureBufferFactory.hpp"

namespace Sindri
{
  class GpuPreviewTextureFactory : public IGpuPreviewTextureFactory
  {
  private:
    std::shared_ptr<ITextureBufferFactory> mTextureBufferFactory;

  public:
    GpuPreviewTextureFactory(
      std::shared_ptr<ITextureBufferFactory> textureBufferFactory);
    ~GpuPreviewTextureFactory() override = default;

    auto
    Create() -> std::shared_ptr<IGpuPreviewTexture> override;
  };
}