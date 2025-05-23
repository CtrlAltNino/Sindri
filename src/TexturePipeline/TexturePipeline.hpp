#pragma once

#include "ITexturePipeline.hpp"
#include "NoiseLayer/INoiseLayer.hpp"
#include "NoiseLayer/INoiseLayerFactory.hpp"
#include "TexturePipeline/ITexturePipeline.hpp"

namespace Sindri
{
  class TexturePipeline : public ITexturePipeline
  {
  private:
    std::shared_ptr<INoiseLayerFactory>       mNoiseLayerFactory;
    std::vector<std::shared_ptr<INoiseLayer>> mNoiseLayers;

  public:
    TexturePipeline() = default;
    ~TexturePipeline() override = default;

    void
    AddLayer(std::filesystem::path luaScriptPath) override;

    void
    RemoveLayer(uint32_t index) override;

    void
    MoveLayer(uint32_t fromIndex, uint32_t toIndex) override;

    auto
    GetLayers() -> std::vector<std::shared_ptr<INoiseLayer>>& override;

    void
    RenderAllSettings() override;
  };
}