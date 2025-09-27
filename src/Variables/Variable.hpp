#pragma once

namespace Sindri
{
  enum class VarKind : uint8_t
  {
    Float,
    Int,
    Vec2,
    Vec3,
    Vec4,
  };

  using NodeVariableValue =
    std::variant<float, int, glm::vec2, glm::vec3, glm::vec4>;

  struct VariableDef
  {
    std::string       name;  // user‑visible label, editable
    VarKind           kind;  // type of the variable
    NodeVariableValue value; // initial value, stored as the concrete type
  };
}