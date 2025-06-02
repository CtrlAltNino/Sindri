#pragma once

#include "NodeTypes.hpp"
#include "TextureExporter.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class DecomposeVec2Node : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeVec2Node()
    {
      setTitle("Decompose (2D)");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<glm::vec2>(
        "Vector2D", glm::vec2(0), ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<float>("X", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec2>("Vector").x; });
      ImFlow::BaseNode::addOUT<float>("Y", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec2>("Vector").y; });
    }

    void
    draw() override
    {
    }
  };

  class DecomposeVec3Node : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeVec3Node()
    {
      setTitle("Decompose (3D)");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->header_bg = ((ImU32)208) | ((ImU32)135 << 8) |
                              ((ImU32)112 << 16) | ((ImU32)255 << 24);

      ImFlow::BaseNode::addIN<glm::vec3>(
        "Vector", glm::vec3(0), ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<float>("X", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec3>("Vector").x; });
      ImFlow::BaseNode::addOUT<float>("Y", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec3>("Vector").y; });
      ImFlow::BaseNode::addOUT<float>("Z", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec3>("Vector").z; });
    }

    void
    draw() override
    {
    }
  };

  class DecomposeVec4Node : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeVec4Node()
    {
      setTitle("Decompose (4D)");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->header_bg = ((ImU32)208) | ((ImU32)135 << 8) |
                              ((ImU32)112 << 16) | ((ImU32)255 << 24);

      ImFlow::BaseNode::addIN<glm::vec4>(
        "Vector", glm::vec4(0), ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<float>("X", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec4>("Vector").x; });
      ImFlow::BaseNode::addOUT<float>("Y", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec4>("Vector").y; });
      ImFlow::BaseNode::addOUT<float>("Z", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec4>("Vector").z; });
      ImFlow::BaseNode::addOUT<float>("W", nullptr)
        ->behaviour([this]() { return getInVal<glm::vec4>("Vector").w; });
    }

    void
    draw() override
    {
    }
  };
}