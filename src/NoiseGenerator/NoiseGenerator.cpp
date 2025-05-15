#include "pch.hpp"

#include "NoiseGenerator.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include "Utility/CoordinateHelper.hpp"
#include <random>

namespace Sindri
{
  void
  NoiseGenerator::FillTexture(CompositionStack&  compositionStack,
                              TextureSettings&   settings,
                              ProceduralTexture& texture)
  {
    // std::mt19937                          gen(settings.mSeed);
    std::vector<float>& data = texture.GetData();
    // std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < data.size(); i++)
    {
      data[i] = compositionStack.Evaluate(
        settings, IndexToCoord(i, settings.mResolution, settings.mDimensions));
    }

    texture.Upload();
  }
}