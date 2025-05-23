#include "pch.hpp"

#include "Helpers/UI.hpp"
#include "NoiseLayer.hpp"
#include <imgui.h>
#include <math.h>
#include <sol/types.hpp>

namespace Sindri
{
  NoiseLayer::NoiseLayer(const std::filesystem::path& luaScriptPath)
    : mPath(luaScriptPath)
  {
    lua.open_libraries(sol::lib::math, sol::lib::base, sol::lib::string);
    lua.script_file(luaScriptPath.string());
    mName = lua["name"];
    sol::table settings = lua["settings"];

    for (auto& pair : settings)
    {
      std::string key = pair.first.as<std::string>();
      sol::object value = pair.second;

      if (value.is<float>())
      {
        mSettings[key] = value.as<float>();
      }
      else if (value.is<int>())
      {
        mSettings[key] = value.as<int>();
      }
      else if (value.is<bool>())
      {
        mSettings[key] = value.as<bool>();
      }
    }
  }

  // Renders ImGui based UI for the settings
  void
  NoiseLayer::RenderSettings()
  {
    ComboEnum("Type", mBlendMode);

    for (auto& pair : mSettings)
    {
      std::string                    key = pair.first;
      std::variant<bool, int, float> value = pair.second;

      if (std::holds_alternative<int>(value))
      {
        int val = std::get<int>(value);
        if (ImGui::DragInt(key.c_str(), &val, 1.0F, 0, 100))
        {
          mSettings[key] = val; // write back
        }
      }
      else if (std::holds_alternative<float>(value))
      {
        float val = std::get<float>(value);
        if (ImGui::DragFloat(key.c_str(), &val, 0.05F, 0.0f, 10.0f))
        {
          mSettings[key] = val; // write back
        }
      }
      else if (std::holds_alternative<bool>(value))
      {
        bool val = std::get<bool>(value);
        if (ImGui::Checkbox(key.c_str(), &val))
        {
          mSettings[key] = val; // write back
        }
      }
    }
  }

  auto
  NoiseLayer::GetName() -> std::string
  {
    return mName;
  }

  auto
  NoiseLayer::GetBlendMode() -> BlendMode
  {
    return mBlendMode;
  }

  auto
  NoiseLayer::GetPath() -> std::filesystem::path
  {
    return mPath;
  }

  auto
  NoiseLayer::GetSettings()
    -> std::map<std::string, std::variant<bool, int, float>>
  {
    return mSettings;
  }
}