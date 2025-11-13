#pragma once

namespace Sindri
{
  class ISindriGui
  {
  public:
    virtual ~ISindriGui() = default;

    virtual void
    Render(float deltaTime) = 0;
  };
}