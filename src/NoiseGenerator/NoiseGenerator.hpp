#pragma once

#include "ProceduralTexture.hpp"

namespace Sindri
{
  class NoiseGenerator
  {
  public:
    NoiseGenerator() = default;

    void
    FillTexture(TextureSettings settings, ProceduralTexture& texture);
  };
}