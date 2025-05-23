#pragma once

#include "NoiseLayer/INoiseLayer.hpp"
#include <map>
#include <sol/sol.hpp>

namespace Sindri
{
  class NoiseLayer : public INoiseLayer
  {
  private:
    std::string           mName;
    std::filesystem::path mPath;
    BlendMode             mBlendMode = BlendMode::Add;
    sol::state            lua;
    std::map<std::string, std::variant<bool, int, float>> mSettings;

  public:
    NoiseLayer(const std::filesystem::path& luaScriptPath);
    ~NoiseLayer() override = default;

    // Renders ImGui based UI for the settings
    void
    RenderSettings() override;

    auto
    GetName() -> std::string override;

    auto
    GetBlendMode() -> BlendMode override;

    auto
    GetPath() -> std::filesystem::path override;

    auto
    GetSettings()
      -> std::map<std::string, std::variant<bool, int, float>> override;
  };
}