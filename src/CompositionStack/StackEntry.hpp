#pragma once

#include "TextureSettings/TextureSettings.hpp"
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
    std::string             mName;
    std::filesystem::path   mPath;
    ComposeType             mComposeType = ComposeType::Add;
    sol::state              lua;
    sol::protected_function mEvaluate;
    sol::table              mSettings;
    std::string             mSerializedSettings;

  public:
    StackEntry(const std::filesystem::path& luaScriptPath);

    // Renders ImGui based UI for the settings
    void
    RenderSettings();

    auto
    GetName() -> std::string;

    auto
    GetComposeType() -> ComposeType;

    void
    Serialize();

    auto
    GetSerializedSettings() -> std::string;

    auto
    GetPath() -> std::filesystem::path;

    // Compute a float value (0.0 - 1.0)
    auto
    Evaluate(std::shared_ptr<TextureSettings> settings, glm::ivec3 coordinate)
      -> float;
  };
}