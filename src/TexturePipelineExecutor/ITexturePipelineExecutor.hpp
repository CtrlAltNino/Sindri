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

    virtual void
    CancelExecution() = 0;

    virtual auto
    IsRunning() -> bool = 0;

    virtual auto
    GetProgress() -> float = 0;
  };
}