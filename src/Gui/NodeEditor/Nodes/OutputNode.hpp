#pragma once

#include "NodeTypes.hpp"
#include "TextureExporter.hpp"
#include "TextureSettings/TextureSettings.hpp"
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

      ImFlow::BaseNode::addIN<float>(
        "R", 0.0F, ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<float>(
        "G", 0.0F, ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<float>(
        "B", 0.0F, ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addIN<float>(
        "A", 0.0F, ImFlow::ConnectionFilter::SameType());
    }

    void
    draw() override
    {
    }
  };
}