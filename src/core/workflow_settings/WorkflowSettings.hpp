#pragma once

#include "TextureTypes.hpp"

namespace Sindri
{
  struct WorkflowSettings
  {
    WorkflowSettings() = default;
    TextureDimension Dimensions = TextureDimension::Texture2D;
    ChannelCount     ChannelCount = ChannelCount::R;
    // glm::ivec3       Resolution = glm::ivec3(512, 512, 512);
    uint32_t Seed = 0;
  };
}