// SubtractNode_variant.h
#include "../NodeTypes.hpp"
#include "ImNodeFlow.h" // adjust path as needed
#include <string>
#include <variant>

namespace Sindri
{
  class OneMinusNode : public ImFlow::BaseNode
  {
  public:
    OneMinusNode()
    {
      setTitle("OneMinus");
      setStyle(ImFlow::NodeStyle::green());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      // add two inputs and one output all typed as the Variant "Scalar"
      addIN<std::function<Scalar(glm::vec2)>>(
        "A",
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

            float res = std::visit([](auto&& lhs) -> float
                                   { return 1.0 - static_cast<float>(lhs); },
                                   a);

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
      double      res = std::visit(
        [](auto&& lhs) { return 1.0 - static_cast<double>(lhs); }, a);
      ImGui::Text("Result: %g", res);
    }
  };
}