#pragma once

#include "NodeTypes.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class Tex1DCoordNode : public ImFlow::BaseNode
  {
  private:
  public:
    Tex1DCoordNode()
    {
      setTitle("Texture Coordinate");
      // setStyle(ImFlow::NodeStyle::red());
      getStyle()->header_bg = ImU32(0);
      ImFlow::BaseNode::addOUT<float>("Vector1D", nullptr);
    }

    void
    draw() override
    {
    }
  };

  class Texture2DCoordNode : public ImFlow::BaseNode
  {
  private:
  public:
    Texture2DCoordNode()
    {
      setTitle("Texture Coordinate");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(191, 97, 106, 255);
      ImFlow::BaseNode::addOUT<glm::vec2>("Vector2D", nullptr);
    }

    void
    draw() override
    {
    }
  };

  class Texture3DCoordNode : public ImFlow::BaseNode
  {
  private:
  public:
    Texture3DCoordNode()
    {
      setTitle("Texture Coordinate");
      setStyle(ImFlow::NodeStyle::brown());
      ImFlow::BaseNode::addOUT<glm::vec3>("Vector3D", nullptr);
    }

    void
    draw() override
    {
    }
  };
}