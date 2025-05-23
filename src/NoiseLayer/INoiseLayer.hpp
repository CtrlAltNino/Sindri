#pragma once

#include <map>
#include <sol/sol.hpp>

namespace Sindri
{
  enum BlendMode
  {
    Add,
    Subtract,
    Multiply,
    Divide,
    Max,
    Min,
    Overlay,
    Replace
  };

  class INoiseLayer
  {
  public:
    virtual ~INoiseLayer() = default;

    // Renders ImGui based UI for the settings
    virtual void
    RenderSettings() = 0;

    virtual auto
    GetName() -> std::string = 0;

    virtual auto
    GetBlendMode() -> BlendMode = 0;

    virtual auto
    GetPath() -> std::filesystem::path = 0;

    virtual auto
    GetSettings() -> std::map<std::string, std::variant<bool, int, float>> = 0;
  };
}