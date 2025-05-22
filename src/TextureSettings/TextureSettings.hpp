#pragma once

namespace Sindri
{
  enum class TextureDimension : uint8_t
  {
    Texture1D,
    Texture2D,
    Texture3D
  };

  struct TextureSettings
  {
    TextureDimension mDimensions = TextureDimension::Texture2D;
    glm::ivec3       mResolution = glm::ivec3(512, 512, 512);
    uint32_t         mSeed = 0;
  };
}