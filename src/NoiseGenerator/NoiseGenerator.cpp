#include "pch.hpp"

#include "NoiseGenerator.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <random>

namespace Sindri
{
  void
  NoiseGenerator::FillTexture(TextureSettings    settings,
                              ProceduralTexture& texture)
  {
    std::mt19937 gen(settings.mSeed);
    switch (settings.mTextureFormat)
    {
      using enum TextureFormat;
      case U8:
        {
          std::vector<unsigned char>& data =
            texture.GetTypedData<unsigned char>();

          std::uniform_int_distribution<> dis(0, 255);
          for (int i = 0; i < data.size(); i++)
          {
            data[i] = static_cast<unsigned char>(dis(gen));
          }
        }
        break;
      case F32:
        {
          std::vector<float>& data = texture.GetTypedData<float>();
          std::uniform_real_distribution<float> dis(0.0f, 1.0f);

          for (int i = 0; i < data.size(); i++)
          {
            data[i] = dis(gen);
          }
        }
        break;
    }

    texture.Upload();
  }
}