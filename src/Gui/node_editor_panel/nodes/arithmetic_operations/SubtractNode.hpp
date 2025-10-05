#pragma once

#include "ImNodeFlow.h"
#include <string>
#include <variant>

namespace Sindri
{
  class SubtractNode : public ImFlow::BaseNode
  {
  public:
    SubtractNode()
    {
      setTitle("Subtract");
      setStyle(ImFlow::NodeStyle::green());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      // add two inputs and one output all typed as the Variant "Scalar"
      addIN<std::function<float(glm::vec2)>>(
        "A",
        [](glm::vec2 vector) -> float { return 0.0F; },
        ImFlow::ConnectionFilter::SameType());
      addIN<std::function<float(glm::vec2)>>(
        "B",
        [](glm::vec2 vector) -> float { return 0.0F; },
        ImFlow::ConnectionFilter::SameType());

      // output behaviour: compute the sum and return a Scalar (we return a
      // double for precision)
      addOUT<std::function<float(glm::vec2)>>("Result")->behaviour(
        [this]()
        {
          return [this](glm::vec2 vector) -> float
          {
            const auto& a =
              getInVal<std::function<float(glm::vec2)>>("A")(vector);
            const auto& b =
              getInVal<std::function<float(glm::vec2)>>("B")(vector);

            float res = a - b;

            return res;
          };
        });
    }

    void
    draw() override
    {
      // Show a simple readout of the computed result (not required — behaviour
      // is where outputs are computed)
      const auto& a = getInVal<std::function<float(glm::vec2)>>("A")({ 0, 0 });
      const auto& b = getInVal<std::function<float(glm::vec2)>>("B")({ 0, 0 });
      double      res = a - b;
      ImGui::Text("Result: %g", res);
    }
  };
}