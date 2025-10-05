#include "pch.hpp"

#include "INoiseLayer.hpp"
#include "NoiseLayer.hpp"
#include "NoiseLayerFactory.hpp"

namespace Sindri
{
  auto
  NoiseLayerFactory::Create(std::filesystem::path scriptPath)
    -> std::shared_ptr<INoiseLayer>
  {
    return std::make_shared<NoiseLayer>(scriptPath);
  }
}