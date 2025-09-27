#pragma once

#include "WorkflowSettings/WorkflowSettings.hpp"
#include <cstdint>

namespace Sindri
{
  using Scalar = std::variant<int, float>;
  using Vector = std::variant<glm::vec2, glm::vec3, glm::vec4>;

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