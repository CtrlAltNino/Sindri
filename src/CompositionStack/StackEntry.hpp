#pragma once

#include "TextureSettings/TextureSettings.hpp"
#include <map>
#include <sol/sol.hpp>

namespace Sindri
{
  enum ComposeType
  {
    Add,
    Multiply
  };

  class StackEntry
  {
  private:
    std::string           mName;
    std::filesystem::path mPath;
    ComposeType           mComposeType = ComposeType::Add;
    sol::state            lua;
    std::map<std::string, std::variant<bool, int, float>> mSettingsMap;

  public:
    StackEntry(const std::filesystem::path& luaScriptPath);

    // Renders ImGui based UI for the settings
    void
    RenderSettings();

    auto
    GetName() -> std::string;

    auto
    GetComposeType() -> ComposeType;

    auto
    GetPath() -> std::filesystem::path;

    auto
    GetSettings() -> std::map<std::string, std::variant<bool, int, float>>;
  };
}