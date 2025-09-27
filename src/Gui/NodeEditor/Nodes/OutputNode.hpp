#pragma once

#include "NodeTypes.hpp"
#include "TextureExporter.hpp"
#include "WorkflowSettings/WorkflowSettings.hpp"
#include <ImNodeFlow.h>

namespace Sindri
{
  /* The simple sum basic node */
  class OutputNode : public ImFlow::BaseNode
  {
  private:
    // TextureDimension mDimension = TextureDimension::Texture2D;
    ChannelCount mChannels = ChannelCount::R;

  public:
    OutputNode()
    {
      setTitle("Output");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(163, 190, 140, 255);

      ImFlow::BaseNode::addIN<std::function<Scalar(glm::vec2)>>(
        "R",
        [](glm::vec2 vector) -> Scalar { return { 0.2f }; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<Scalar(glm::vec2)>>(
        "G",
        [](glm::vec2 vector) -> Scalar { return { 0.4f }; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<Scalar(glm::vec2)>>(
        "B",
        [](glm::vec2 vector) -> Scalar { return { 0.6f }; },
        ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<std::function<Scalar(glm::vec2)>>(
        "A",
        [](glm::vec2 vector) -> Scalar { return { 0.8f }; },
        ImFlow::ConnectionFilter::SameType());
    }

    void
    draw() override
    {

      for (int x = 0; x < 64; ++x)
      {
        for (int y = 0; y < 64; ++y)
        {
          // getInVal<std::function<float(glm::vec2)>>("R")({ x, y });
        }
      }

      const auto& r = getInVal<std::function<Scalar(glm::vec2)>>("R")({ 1, 2 });
      const auto& g = getInVal<std::function<Scalar(glm::vec2)>>("G")({ 1, 2 });
      const auto& b = getInVal<std::function<Scalar(glm::vec2)>>("B")({ 1, 2 });
      const auto& a = getInVal<std::function<Scalar(glm::vec2)>>("A")({ 1, 2 });
      double      resR =
        std::visit([](auto&& lhs) { return static_cast<float>(lhs); }, r);
      double resG =
        std::visit([](auto&& lhs) { return static_cast<float>(lhs); }, g);
      double resB =
        std::visit([](auto&& lhs) { return static_cast<float>(lhs); }, b);
      double resA =
        std::visit([](auto&& lhs) { return static_cast<float>(lhs); }, a);

      ImGui::Text("R: %g", resR);
      ImGui::Text("G: %g", resG);
      ImGui::Text("B: %g", resB);
      ImGui::Text("A: %g", resA);
    }
  };
}