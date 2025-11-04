#pragma once

#include "ImNodeFlow.h" // adjust path as needed
#include "Variable.hpp"
#include <string>

namespace Sindri
{
  class VariableNode : public ImFlow::BaseNode
  {
  private:
    // Variable Reference
    VariableDef* mVariable;

  public:
    VariableNode(VariableDef* variableRef)
      : mVariable(variableRef)
    {
      setTitle(mVariable->name);
      setStyle(ImFlow::NodeStyle::cyan());

      switch (mVariable->kind)
      {
        case VarKind::Float:
          addOUT<std::function<float(glm::vec2)>>("Value (Float)", nullptr)
            ->behaviour(
              [this]()
              {
                return [this](glm::vec2 vector) -> float
                { return std::get<float>(mVariable->value); };
              });
          break;
        case VarKind::Int:
          addOUT<std::function<int(glm::vec2)>>("Value (Int)", nullptr)
            ->behaviour(
              [this]()
              {
                return [this](glm::vec2 vector) -> int
                { return std::get<int>(mVariable->value); };
              });
          break;
        case VarKind::Vec2:
          addOUT<std::function<glm::vec2(glm::vec2)>>("Value (Vec2)", nullptr)
            ->behaviour(
              [this]()
              {
                return [this](glm::vec2 vector) -> glm::vec2
                { return std::get<glm::vec2>(mVariable->value); };
              });
          break;
        case VarKind::Vec3:
          addOUT<std::function<glm::vec3(glm::vec2)>>("Value (Vec3)", nullptr)
            ->behaviour(
              [this]()
              {
                return [this](glm::vec2 vector) -> glm::vec3
                { return std::get<glm::vec3>(mVariable->value); };
              });
          break;
        case VarKind::Vec4:
          addOUT<std::function<glm::vec4(glm::vec2)>>("Value (Vec4)", nullptr)
            ->behaviour(
              [this]()
              {
                return [this](glm::vec2 vector) -> glm::vec4
                { return std::get<glm::vec4>(mVariable->value); };
              });
          break;
      }
    }

    void
    draw() override
    {
      // Show a simple readout of the computed result (not required — behaviour
      // is where outputs are computed)
      // const auto& a = getInVal<Scalar>("A");
      // const auto& b = getInVal<Scalar>("B");
      // double      res = std::visit(
      //   [](auto&& lhs, auto&& rhs)
      //   { return static_cast<double>(lhs) / static_cast<double>(rhs); },
      //   a,
      //   b);
      // ImGui::Text("Result: %g", res);
    }
  };
}
