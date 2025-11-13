#pragma once

#include "TextureExporter.hpp"
#include "TextureTypes.hpp"
#include "WorkflowSettings.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  class DecomposeVec2Node : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeVec2Node()
    {
      setTitle("Decompose Vec2");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<glm::vec2(TexCoord)>>(
        "In (Vec2)",
        [](glm::vec3 vector) -> glm::vec2 { return { 0, 0 }; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("X", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec2(TexCoord)>>("In (Vec2)")(
                       texCoord)
                .x;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Y", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec2(glm::vec3)>>("In (Vec2)")(
                       texCoord)
                .y;
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

  class DecomposeVec3Node : public ImFlow::BaseNode
  {
  private:
  public:
    DecomposeVec3Node()
    {
      setTitle("Decompose Vec3");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<glm::vec3(TexCoord)>>(
        "In (Vec3)",
        [](TexCoord texCoord) -> glm::vec3 { return { 0, 0, 0 }; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("X", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec3(TexCoord)>>("In (Vec3)")(
                       texCoord)
                .x;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Y", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec3(TexCoord)>>("In (Vec3)")(
                       texCoord)
                .y;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Z", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec3(TexCoord)>>("In (Vec3)")(
                       texCoord)
                .z;
            };
          });
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
      setTitle("Decompose Vec4");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(208, 135, 112, 255);

      ImFlow::BaseNode::addIN<std::function<glm::vec4(TexCoord)>>(
        "In (Vec4)",
        [](TexCoord texCoord) -> glm::vec4 { return { 0, 0, 0, 0 }; },
        ImFlow::ConnectionFilter::SameType());

      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("X", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec4(TexCoord)>>("In (Vec4)")(
                       texCoord)
                .x;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Y", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec4(TexCoord)>>("In (Vec4)")(
                       texCoord)
                .y;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("Z", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec4(TexCoord)>>("In (Vec4)")(
                       texCoord)
                .z;
            };
          });
      ImFlow::BaseNode::addOUT<std::function<float(TexCoord)>>("W", nullptr)
        ->behaviour(
          [this]()
          {
            return [this](TexCoord texCoord) -> float
            {
              return getInVal<std::function<glm::vec4(TexCoord)>>("In (Vec4)")(
                       texCoord)
                .w;
            };
          });
    }

    void
    draw() override
    {
    }
  };
}