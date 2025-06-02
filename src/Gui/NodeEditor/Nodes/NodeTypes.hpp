#pragma once

#include "TextureSettings/TextureSettings.hpp"
#include <cstdint>

namespace Sindri
{
  struct UvType
  {
    TextureDimension Dimension;
  };

  enum class MathOperationType : uint8_t
  {
    Add,
    Subtract,
    Multiply,
    Divide
  };

  enum class MathDataType : uint8_t
  {
    Float,
    Integer,
    Vec2,
    Vec3,
  };
}