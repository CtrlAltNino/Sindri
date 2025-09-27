// SubtractNode_variant.h
#include "../NodeTypes.hpp"
#include "ImNodeFlow.h" // adjust path as needed
#include <cmath>
#include <string>
#include <variant>

namespace Sindri
{
  class PowNode : public ImFlow::BaseNode
  {
  public:
    PowNode()
    {
      setTitle("Pow");
      setStyle(ImFlow::NodeStyle::green());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      // add two inputs and one output all typed as the Variant "Scalar"
      addIN<std::function<Scalar(glm::vec2)>>(
        "A",
        [](glm::vec2 vector) -> Scalar { return { 0 }; },
        ImFlow::ConnectionFilter::SameType());
      addIN<std::function<Scalar(glm::vec2)>>(
        "B",
        [](glm::vec2 vector) -> Scalar { return { 0 }; },
        ImFlow::ConnectionFilter::SameType());

      // output behaviour: compute the sum and return a Scalar (we return a
      // double for precision)
      addOUT<std::function<Scalar(glm::vec2)>>("Result")->behaviour(
        [this]()
        {
          return [this](glm::vec2 vector) -> Scalar
          {
            const auto& a =
              getInVal<std::function<Scalar(glm::vec2)>>("A")(vector);
            const auto& b =
              getInVal<std::function<Scalar(glm::vec2)>>("B")(vector);

            float res = std::visit(
              [](auto&& lhs, auto&& rhs) -> float
              {
                return std::pow(static_cast<float>(lhs),
                                static_cast<float>(rhs));
              },
              a,
              b);

            return res;
          };
        });
    }

    void
    draw() override
    {
      // Show a simple readout of the computed result (not required — behaviour
      // is where outputs are computed)
      const auto& a = getInVal<std::function<Scalar(glm::vec2)>>("A")({ 0, 0 });
      const auto& b = getInVal<std::function<Scalar(glm::vec2)>>("B")({ 0, 0 });
      double      res = std::visit(
        [](auto&& lhs, auto&& rhs)
        {
          return std::pow(static_cast<double>(lhs), static_cast<double>(rhs));
        },
        a,
        b);
      ImGui::Text("Result: %g", res);
    }
  };
}