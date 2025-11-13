#pragma once

#include "IGpuPreviewTexture.hpp"
namespace Sindri
{
  class PreviewableNode
  {
  private:
    std::shared_ptr<IGpuPreviewTexture> mPreviewTexture;

  public:
    void
    RenderPreview();

    void
    Update(std::function<float(glm::vec3)> fillFunction);
  };
}