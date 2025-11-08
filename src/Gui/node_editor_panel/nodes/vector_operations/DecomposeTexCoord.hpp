#pragma once

#include "TextureExporter.hpp"
#include "WorkflowSettings.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class DecomposeTexCoordNode : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeTexCoordNode()
    {
      setTitle("Decompose TexCoord");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<TexCoord(TexCoord)>>(
        "In (TexCoord)",
        [](TexCoord vector) -> TexCoord { return { 0, 0, 0 }; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("X", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord coord) -> float
            {
              return getInVal<std::function<TexCoord(TexCoord)>>(
                       "In (TexCoord)")(coord)
                .x;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Y", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord coord) -> float
            {
              return getInVal<std::function<TexCoord(TexCoord)>>(
                       "In (TexCoord)")(coord)
                .y;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Z", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord coord) -> float
            {
              return getInVal<std::function<TexCoord(TexCoord)>>(
                       "In (TexCoord)")(coord)
                .z;
            };
          });
    }

    void
    draw() override
    {
      /*const auto& b =
        getInVal<std::function<glm::vec2(glm::vec3)>>("Vector2D")({ 0, 0 });
      ImGui::Text("X: %g | Y: %g", b.x, b.y);*/
    }
  };
}