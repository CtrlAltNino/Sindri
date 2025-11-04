#pragma once

#include "CoordinateHelper.hpp"
#include "IPreviewableNode.hpp"
#include "TextureTypes.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class UVNode
    : public ImFlow::BaseNode
    , public IPreviewableNode
  {
  private:
    std::shared_ptr<ImFlow::OutPin<std::function<UVCoordinate(UVCoordinate)>>>
      mOutPin;

  public:
    UVNode()
    {
      setTitle("UV");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(191, 97, 106, 255);
    }

    void
    draw() override
    {
      // Draw Preview
    }

    static auto
    generateOutPinUid(TextureDimension dimensions) -> std::string
    {
      switch (dimensions)
      {
        case TextureDimension::Texture1D: return "Texture Cooridnate (float)";
        case TextureDimension::Texture2D: return "Texture Coordinate (vec2)";
        case TextureDimension::Texture3D: return "Texture Coordinate (vec3)";
      }
    }

    void
    setup(TextureDimension dimensions)
    {
      if (mOutPin == nullptr)
      {
        mOutPin =
          ImFlow::BaseNode::addOUT<std::function<UVCoordinate(UVCoordinate)>>(
            "yeet", nullptr);

        mOutPin->behaviour(
          [this]()
          {
            return [this](UVCoordinate coordinate) -> UVCoordinate
            { return coordinate; };
          });
      }

      mOutPin->renderer(
        [dimensions](auto* pin)
        {
          auto* castedPin = dynamic_cast<
            ImFlow::OutPin<std::function<UVCoordinate(UVCoordinate)>>*>(pin);
          // auto pp = dynamic_cast<
          //   ImFlow::OutPin<std::function<UVCoordinate(UVCoordinate)>>*>(
          //   p);
          ImGui::Text("%s", generateOutPinUid(dimensions).c_str());

          pin->drawSocket();
          pin->drawDecoration();
        });

      // mOutPin.
    }
  };
}