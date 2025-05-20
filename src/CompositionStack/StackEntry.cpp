#include "pch.hpp"

#include "Helpers/UI.hpp"
#include "StackEntry.hpp"
#include <imgui.h>
#include <math.h>
#include <sol/types.hpp>

namespace Sindri
{
  StackEntry::StackEntry(const std::filesystem::path& luaScriptPath)
    : mPath(luaScriptPath)
  {
    lua.open_libraries(sol::lib::math, sol::lib::base, sol::lib::string);
    lua.script_file(luaScriptPath.string());
    mEvaluate = lua["evaluate"];
    mName = lua["name"];
    mSettings = lua["settings"];
  }

  // Renders ImGui based UI for the settings
  void
  StackEntry::RenderSettings()
  {
    ComboEnum("Type", mComposeType);

    for (auto& pair : mSettings)
    {
      std::string key = pair.first.as<std::string>();
      sol::object value = pair.second;

      if (value.is<int>())
      {
        int val = value.as<int>();
        if (ImGui::SliderInt(key.c_str(), &val, 0, 100))
        {
          mSettings[key] = val; // write back
        }
      }
      else if (value.is<float>())
      {
        float val = value.as<float>();
        if (ImGui::SliderFloat(key.c_str(), &val, 0.0f, 10.0f))
        {
          mSettings[key] = val; // write back
        }
      }
      else if (value.is<bool>())
      {
        bool val = value.as<bool>();
        if (ImGui::Checkbox(key.c_str(), &val))
        {
          mSettings[key] = val; // write back
        }
      }
      else if (value.is<std::string>())
      {
        std::string val = value.as<std::string>();
        char        buffer[128];
        std::snprintf(buffer, sizeof(buffer), "%s", val.c_str());
        if (ImGui::InputText(key.c_str(), buffer, sizeof(buffer)))
        {
          mSettings[key] = std::string(buffer); // write back
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

  // Compute a float value (0.0 - 1.0)
  auto
  StackEntry::Evaluate(std::shared_ptr<TextureSettings> settings,
                       glm::ivec3                       coordinate) -> float
  {
    float normalizedX = (float)coordinate.x / (float)settings->mResolution.x;
    float normalizedY = (float)coordinate.y / (float)settings->mResolution.y;
    float normalizedZ = (float)coordinate.z / (float)settings->mResolution.z;

    sol::protected_function_result result =
      mEvaluate(normalizedX, normalizedY, normalizedZ, settings->mSeed);

    float resultFloat = 0.0F;

    if (!result.valid())
    {
      sol::error err = result;
      std::cerr << "Lua error: " << err.what() << std::endl;
    }
    else
    {
      resultFloat = result; // or result.get<float>() for safety
    }

    return resultFloat;
  }

  void
  StackEntry::Serialize()
  {
    // return lua["string"]["dump"](lua["evaluate"]);
    // TODO: Use serpent to serialize the settings table
    mSerializedSettings = "";
  }

  auto
  StackEntry::GetSerializedSettings() -> std::string
  {
    return mSerializedSettings;
  }

  auto
  StackEntry::GetPath() -> std::filesystem::path
  {
    return mPath;
  }
}