#include "pch.hpp"

#include "Helpers/UI.hpp"
#include "NoiseLayer.hpp"
#include <imgui.h>
#include <sol/types.hpp>
#include <utility>

namespace Sindri
{
  NoiseLayer::NoiseLayer(std::filesystem::path luaScriptPath)
    : mPath(std::move(luaScriptPath))
  {
    ReloadScriptFile();
  }

  // Renders ImGui based UI for the settings
  void
  NoiseLayer::RenderSettings()
  {
    ImGui::Checkbox("Enabled", &mEnabled);
    ComboEnum("Blend mode", mBlendMode);
    ImGui::SliderFloat("Contribution", &mContribution, 0.0F, 1.0F, "%.2F");

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
  NoiseLayer ::IsEnabled() -> bool
  {
    return mEnabled;
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

  auto
  NoiseLayer::GetContribution() -> float
  {
    return mContribution;
  }

  void
  NoiseLayer::ReloadScriptFile()
  {
    mLua = sol::state{};
    mLua.open_libraries(sol::lib::math, sol::lib::base);
    mLua.script_file(mPath.string());
    mName = mLua["Name"];
    sol::table settings = mLua["Settings"];

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
}