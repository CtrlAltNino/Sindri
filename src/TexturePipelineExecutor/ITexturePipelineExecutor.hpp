#pragma once

#include "TextureSettings/TextureSettings.hpp"

namespace Sindri
{
  class ITexturePipelineExecutor
  {
  public:
    virtual ~ITexturePipelineExecutor() = default;

    virtual void
    ExecutePipeline(TextureSettings settings) = 0;
  };
}