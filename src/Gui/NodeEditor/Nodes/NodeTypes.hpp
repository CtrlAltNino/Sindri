#pragma once

#include "WorkflowSettings/WorkflowSettings.hpp"
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
    Divide,
    Multiply,
    Negate,
    OneMinus,
    Pow,
    Sqrt,
    Subtract,
  };

  enum class MathDataType : uint8_t
  {
    Float,
    Integer,
    Vec2,
    Vec3,
  };
}