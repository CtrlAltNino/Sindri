#pragma once

#include "NoiseLayer/INoiseLayer.hpp"

namespace Sindri
{
  class ITexturePipeline
  {
  public:
    virtual ~ITexturePipeline() = default;

    virtual void
    AddLayer(std::filesystem::path luaScriptPath) = 0;

    virtual void
    RemoveLayer(uint32_t index) = 0;

    virtual void
    MoveLayer(uint32_t fromIndex, uint32_t toIndex) = 0;

    virtual auto
    GetLayers() -> std::vector<std::shared_ptr<INoiseLayer>>& = 0;

    virtual void
    RenderAllSettings() = 0;
  };
}