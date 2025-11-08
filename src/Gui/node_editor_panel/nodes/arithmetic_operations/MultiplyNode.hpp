#pragma once

#include "ImNodeFlow.h"
#include <string>
#include <variant>

namespace Sindri
{
  class MultiplyNode : public ImFlow::BaseNode
  {
  public:
    MultiplyNode()
    {
      setTitle("Multiply");
      setStyle(ImFlow::NodeStyle::green());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      // add two inputs and one output all typed as the Variant "Scalar"
      // add two inputs and one output all typed as the Variant "Scalar"
      addIN<std::function<float(glm::vec3)>>(
        "A",
        [](glm::vec3 vector) -> float { return 0.0F; },
        ImFlow::ConnectionFilter::SameType());
      addIN<std::function<float(glm::vec3)>>(
        "B",
        [](glm::vec3 vector) -> float { return 0.0F; },
        ImFlow::ConnectionFilter::SameType());

      // output behaviour: compute the sum and return a Scalar (we return a
      // double for precision)
      addOUT<std::function<float(glm::vec3)>>("Result")->behaviour(
        [this]()
        {
          return [this](glm::vec3 vector) -> float
          {
            const auto& aValue =
              getInVal<std::function<float(glm::vec3)>>("A")(vector);
            const auto& bValue =
              getInVal<std::function<float(glm::vec3)>>("B")(vector);

            float res = aValue * bValue;

            return res; // stored as the double alternative in the variant
          };
        });
    }

    void
    draw() override
    {
      // Show a simple readout of the computed result (not required — behaviour
      // is where outputs are computed)
      const auto& aValue =
        getInVal<std::function<float(glm::vec3)>>("A")({ 0, 0, 0 });
      const auto& bValue =
        getInVal<std::function<float(glm::vec3)>>("B")({ 0, 0, 0 });

      ImGui::Text("Result: %g", aValue * bValue);
    }
  };
}