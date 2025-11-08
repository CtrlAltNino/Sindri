#pragma once

namespace Sindri
{
  using TexCoord = glm::vec3;
  enum class TextureDimension : uint8_t
  {
    Texture1D,
    Texture2D,
    Texture3D
  };

  enum class FileFormat : uint8_t
  {
    PNG,
    TGA,
    EXR,
    HDR,
    DDS,
    KTX,
    KTX2
  };

  enum class DataType
  {
    UNorm8,
    UNorm16,
    Float16,
    Float32
  };
  enum class ChannelCount
  {
    R = 1,
    RG = 2,
    RGB = 3,
    RGBA = 4
  };
  enum class CompressionType
  {
    None,
    BC1,
    BC3,
    BC4,
    BC5,
    BC6H,
    BC7,
    ASTC
  };
}