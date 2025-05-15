#pragma once

namespace Sindri
{
  enum class TextureDimension : uint8_t
  {
    Texture1D,
    Texture2D,
    Texture3D
  };

  enum class OutputFormat : uint8_t
  {
    PNG,
    TIFF
  };

  enum class TextureFormat : uint8_t
  {
    U8, // unsigned 8-bit
    // F16, // half float
    F32, // full float
  };

  struct TextureSettings
  {
    TextureDimension mDimensions = TextureDimension::Texture2D;
    OutputFormat     mOutputFormat = OutputFormat::PNG;
    TextureFormat    mTextureFormat = TextureFormat::U8;
    glm::ivec3       mResolution = glm::ivec3(512, 512, 512);
    uint32_t         mSeed = 0;
  };
}