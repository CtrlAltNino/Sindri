#pragma once

#include "CompositionStack.hpp"
#include "ProceduralTexture.hpp"

namespace Sindri
{
  class NoiseGenerator
  {
  public:
    NoiseGenerator() = default;

    void
    FillTexture(CompositionStack&  compositionStack,
                TextureSettings&   settings,
                ProceduralTexture& texture);
  };
}