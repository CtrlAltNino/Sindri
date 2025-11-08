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
    std::shared_ptr<ImFlow::OutPin<std::function<TexCoord(TexCoord)>>> mOutPin;

  public:
    UVNode(std::shared_ptr<IGpuPreviewTexture> previewTexture)
      : IPreviewableNode(previewTexture)
    {
      setTitle("UV");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(191, 97, 106, 255);

      mOutPin = ImFlow::BaseNode::addOUT<std::function<TexCoord(TexCoord)>>(
        "TexCoord", nullptr);
      mOutPin->behaviour(
        [this]()
        {
          return [this](TexCoord coordinate) -> TexCoord { return coordinate; };
        });

      GetPreviewTexture()->GetTextureBuffer()->Reserve(128, 128, 3);
      auto& tempBuffer = GetPreviewTexture()->GetTextureBuffer()->GetTempData();
      const int width = 128;
      const int height = 128;
      const int channels = 3;
      int       index = 0;

      for (int y = 0; y < height; ++y)
      {
        for (int x = 0; x < width; ++x)
        {
          float u = static_cast<float>(x) / (width - 1);
          float v = static_cast<float>(y) / (height - 1);

          uint8_t r = static_cast<uint8_t>(u * 255);
          uint8_t g = static_cast<uint8_t>(v * 255);
          uint8_t b = 0;

          // int index = (y * width + x) * channels;
          tempBuffer[index++] = u;
          tempBuffer[index++] = v;
          tempBuffer[index++] = 0.0F;
        }
      }

      GetPreviewTexture()->GetTextureBuffer()->PromoteTemp();
    }

    void
    draw() override
    {
      if (!GetPreviewTexture()->GetIsUploaded())
      {
        GetPreviewTexture()->Upload();
      }

      // Draw Preview
      ImGui::Image((ImTextureID)GetPreviewTexture()->GetTextureId(),
                   ImVec2(128, 128));
    }
  };
}