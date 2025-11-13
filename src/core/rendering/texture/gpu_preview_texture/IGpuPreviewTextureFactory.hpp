#pragma once

#include "IGpuPreviewTexture.hpp"
namespace Sindri
{
  class IGpuPreviewTextureFactory
  {
  public:
    virtual ~IGpuPreviewTextureFactory() = default;

    virtual auto
    Create() -> std::shared_ptr<IGpuPreviewTexture> = 0;
  };
}