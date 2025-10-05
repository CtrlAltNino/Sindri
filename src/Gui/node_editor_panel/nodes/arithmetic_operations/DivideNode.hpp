#pragma once

#include "ImNodeFlow.h"
#include "NodeTypes.hpp"
#include <string>
#include <variant>

namespace Sindri
{
  class DivideNode : public ImFlow::BaseNode
  {
  public:
    DivideNode()
    {
      setTitle("Divide");
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
        [](glm::vec2 vector) -> float { return 1.0F; },
        ImFlow::ConnectionFilter::SameType());

      // output behaviour: compute the sum and return a Scalar (we return a
      // double for precision)
      addOUT<std::function<float(glm::vec2)>>("Result")->behaviour(
        [this]()
        {
          return [this](glm::vec2 vector) -> float
          {
            const auto& aValue =
              getInVal<std::function<float(glm::vec2)>>("A")(vector);
            const auto& bValue =
              getInVal<std::function<float(glm::vec2)>>("B")(vector);

            return aValue /
                   bValue; // stored as the double alternative in the variant
          };
        });
    }

    void
    draw() override
    {
      const auto& aValue =
        getInVal<std::function<float(glm::vec2)>>("A")({ 0, 0 });
      const auto& bValue =
        getInVal<std::function<float(glm::vec2)>>("B")({ 0, 0 });

      float res = aValue / bValue;

      ImGui::Text("Result: %g", res);
    }
  };
}