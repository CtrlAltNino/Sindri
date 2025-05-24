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
    TextureSettings() = default;
    TextureDimension Dimensions = TextureDimension::Texture2D;
    glm::ivec3       Resolution = glm::ivec3(512, 512, 512);
    uint32_t         Seed = 0;
  };
}