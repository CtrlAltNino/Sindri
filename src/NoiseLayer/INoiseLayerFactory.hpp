#pragma once

#include "NoiseLayer/INoiseLayer.hpp"

namespace Sindri
{
  class INoiseLayerFactory
  {
  public:
    virtual ~INoiseLayerFactory() = default;

    virtual auto
    Create(std::filesystem::path scriptPath)
      -> std::shared_ptr<INoiseLayer> = 0;
  };
}