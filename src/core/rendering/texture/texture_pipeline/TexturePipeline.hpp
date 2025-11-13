#pragma once

#include "INoiseLayer.hpp"
#include "INoiseLayerFactory.hpp"
#include "ITexturePipeline.hpp"


namespace Sindri
{
  class TexturePipeline : public ITexturePipeline
  {
  private:
    std::shared_ptr<INoiseLayerFactory>       mNoiseLayerFactory;
    std::vector<std::shared_ptr<INoiseLayer>> mNoiseLayers;

  public:
    TexturePipeline(std::shared_ptr<INoiseLayerFactory> noiseLayerFactory);
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