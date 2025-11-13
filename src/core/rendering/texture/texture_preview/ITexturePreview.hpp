#pragma once

namespace Sindri
{
  class ITexturePreview
  {
  public:
    virtual ~ITexturePreview() = default;

    virtual void
    Init() = 0;

    virtual void
    Render(glm::vec2 resolution, float deltaTime) = 0;

    virtual void
    RenderSettings() = 0;
  };
}