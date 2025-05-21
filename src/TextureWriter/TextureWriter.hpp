#pragma once

namespace Sindri
{
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

  struct TextureOutputSettings
  {
  };

  class TextureWriter
  {
  };
}