#include "pch.hpp"

#include "Helpers/UI.hpp"
#include "StackEntry.hpp"
#include <imgui.h>
#include <math.h>
#include <sol/types.hpp>
#include <variant>

namespace Sindri
{
  StackEntry::StackEntry(const std::filesystem::path& luaScriptPath)
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
      std::cout << key << " raw float value" << value.as<float>() << std::endl;

      if (value.is<float>())
      {
        std::cout << key << " is of type float" << std::endl;
        mSettingsMap[key] = value.as<float>();
      }
      else if (value.is<int>())
      {
        std::cout << key << " is of type int" << std::endl;
        mSettingsMap[key] = value.as<int>();
      }
      else if (value.is<bool>())
      {
        std::cout << key << " is of type bool" << std::endl;
        mSettingsMap[key] = value.as<bool>();
      }
      else
      {
        std::cout << key << " is of unknown type" << std::endl;
      }
    }
  }

  // Renders ImGui based UI for the settings
  void
  StackEntry::RenderSettings()
  {
    ComboEnum("Type", mComposeType);

    for (auto& pair : mSettingsMap)
    {
      std::string                    key = pair.first;
      std::variant<bool, int, float> value = pair.second;

      if (std::holds_alternative<int>(value))
      {
        int val = std::get<int>(value);
        if (ImGui::DragInt(key.c_str(), &val, 1.0F, 0, 100))
        {
          mSettingsMap[key] = val; // write back
        }
      }
      else if (std::holds_alternative<float>(value))
      {
        float val = std::get<float>(value);
        if (ImGui::DragFloat(key.c_str(), &val, 0.05F, 0.0f, 10.0f))
        {
          mSettingsMap[key] = val; // write back
        }
      }
      else if (std::holds_alternative<bool>(value))
      {
        bool val = std::get<bool>(value);
        if (ImGui::Checkbox(key.c_str(), &val))
        {
          mSettingsMap[key] = val; // write back
        }
      }
    }
  }

  auto
  StackEntry::GetName() -> std::string
  {
    return mName;
  }

  auto
  StackEntry::GetComposeType() -> ComposeType
  {
    return mComposeType;
  }

  auto
  StackEntry::GetPath() -> std::filesystem::path
  {
    return mPath;
  }

  auto
  StackEntry::GetSettings()
    -> std::map<std::string, std::variant<bool, int, float>>
  {
    return mSettingsMap;
  }
}