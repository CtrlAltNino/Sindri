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
    sol::state              lua;
    sol::protected_function mEvaluate;
    sol::table              mSettings;
    std::string             mName;
    ComposeType             mComposeType = ComposeType::Add;

  public:
    StackEntry(const std::filesystem::path& luaScriptPath);

    // Renders ImGui based UI for the settings
    void
    RenderSettings();

    auto
    GetName() -> std::string;

    auto
    GetComposeType() -> ComposeType;

    // Compute a float value (0.0 - 1.0)
    auto
    Evaluate(std::shared_ptr<TextureSettings> settings, glm::ivec3 coordinate)
      -> float;
  };
}