#pragma once

#include "TextureExporter.hpp"
#include "WorkflowSettings.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class ComposeVec2Node : public ImFlow::BaseNode
  {
  private:
  public:
    ComposeVec2Node()
    {
      setTitle("Compose Vec2");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "X (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "Y (float)",
        [](glm::vec3 texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<glm::vec2(TexCoord)>>("Out (Vec2)",
                                                                   nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> glm::vec2
            {
              return { getInVal<std::function<float(glm::vec3)>>("X (float)")(
                         texCoord),
                       getInVal<std::function<float(glm::vec3)>>("Y (float)")(
                         texCoord) };
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

  class ComposeVec3Node : public ImFlow::BaseNode
  {
  private:
  public:
    ComposeVec3Node()
    {
      setTitle("Compose Vec3");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "X (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "Y (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "Z (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<glm::vec3(TexCoord)>>("Out (Vec3)",
                                                                   nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> glm::vec3
            {
              return {
                getInVal<std::function<float(TexCoord)>>("X (float)")(texCoord),
                getInVal<std::function<float(TexCoord)>>("Y (float)")(texCoord),
                getInVal<std::function<float(TexCoord)>>("Z (float)")(texCoord)
              };
            };
          });
    }

    void
    draw() override
    {
    }
  };

  class ComposeVec4Node : public ImFlow::BaseNode
  {
  private:
  public:
    ComposeVec4Node()
    {
      setTitle("Compose Vec4");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "X (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "Y (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "Z (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<float(TexCoord)>>(
        "W (float)",
        [](TexCoord texCoord) -> float { return 0; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<glm::vec3(TexCoord)>>("Out (Vec4)",
                                                                   nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> glm::vec4
            {
              return {
                getInVal<std::function<float(TexCoord)>>("X (float)")(texCoord),
                getInVal<std::function<float(TexCoord)>>("Y (float)")(texCoord),
                getInVal<std::function<float(TexCoord)>>("Z (float)")(texCoord),
                getInVal<std::function<float(TexCoord)>>("W (float)")(texCoord)
              };
            };
          });
    }

    void
    draw() override
    {
    }
  };
}