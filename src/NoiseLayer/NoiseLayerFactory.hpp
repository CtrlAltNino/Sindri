#pragma once

#include "NoiseLayer/INoiseLayerFactory.hpp"

namespace Sindri
{
  class NoiseLayerFactory : public INoiseLayerFactory
  {
  public:
    NoiseLayerFactory() = default;
    ~NoiseLayerFactory() override = default;

    auto
    Create(std::filesystem::path scriptPath)
      -> std::shared_ptr<INoiseLayer> override;
  };
}