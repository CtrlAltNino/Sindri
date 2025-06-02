#pragma once

#include "Helper/FileHelper.hpp"
#include "NodeTypes.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>
#include <sol/sol.hpp>

namespace Sindri
{
  /* The simple sum basic node */
  class ScriptNode : public ImFlow::BaseNode
  {
  private:
    int                                mSelectedScriptIndex = 0;
    std::vector<std::filesystem::path> mScripts;
    // std::filesystem::path              mPath;
    //  BlendMode                          mBlendMode = BlendMode::Add;
    sol::state                                            mLua;
    std::map<std::string, std::variant<bool, int, float>> mSettings;
    // bool                                                  mEnabled = true;
    // float                                                 mContribution
    // = 1.0F;

    auto
    GetLuaScripts() -> std::vector<std::filesystem::path>
    {
      std::vector<std::filesystem::path> scripts;
      for (const auto& entry : std::filesystem::directory_iterator("lua"))
      {
        if (entry.is_regular_file() && entry.path().extension() == ".lua")
        {
          scripts.push_back(entry.path()); // relative name
        }
      }
      return scripts;
    }

    void
    ReloadScriptFile()
    {
      mLua = sol::state{};
      mLua.open_libraries(sol::lib::math, sol::lib::base);
      mLua.script_file(mScripts[mSelectedScriptIndex].string());
      // mName = mLua["Name"];
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

    void
    LuaScriptSelector()
    {
      // ImGui::SeparatorText("Script");

      /*if (ImGui::Button("Refresh list"))
      {
        mSelectedScriptIndex = 0;
        mScripts = GetLuaScripts();
      }

      ImGui::SameLine();

      if (ImGui::Button("Open directory"))
      {
        OpenInFileExplorer("lua");
      }*/

      ImGui::SetNextItemWidth(200.f);

      // Combo Box
      // TODO: ID
      if (ImGui::BeginCombo(
            "##ScriptSelector",
            mSelectedScriptIndex >= 0 && mSelectedScriptIndex < mScripts.size()
              ? mScripts[mSelectedScriptIndex].filename().string().c_str()
              : "Select..."))
      {
        for (int i = 0; i < mScripts.size(); ++i)
        {
          bool isSelected = (mSelectedScriptIndex == i);
          if (ImGui::Selectable(mScripts[i].filename().string().c_str(),
                                isSelected))
          {
            mSelectedScriptIndex = i;
          }
          if (isSelected)
          {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      // ImGui::SameLine();

      if (ImGui::Button("Load script"))
      {
        ReloadScriptFile();
      }

      // ImGui::SetNextItemWidth(200.f);
      // ImGui::SeparatorText("Settings");
      ImGui::Spacing();

      RenderSettings();

      // Add Button
      /*ImGui::PushStyleColor(
        ImGuiCol_Button,
        ImVec4(163.0F / 255.0F, 190.0F / 255.0F, 140.0F / 255.0F, 1.0F));
      ImGui::PushStyleColor(
        ImGuiCol_ButtonHovered,
        ImVec4(189.0F / 255.0F, 220.0F / 255.0F, 162.0F / 255.0F, 1.0F));
      ImGui::PushStyleColor(
        ImGuiCol_ButtonActive,
        ImVec4(138.0F / 255.0F, 160.0F / 255.0F, 118.0F / 255.0F, 1.0F));
      ImGui::PushStyleColor(
        ImGuiCol_Text,
        ImVec4(76.0F / 255.0F, 86.0F / 255.0F, 106.0F / 255.0F, 1.0F));
      if (ImGui::Button("Add layer"))
      {
        if (mSelectedScriptIndex >= 0 && mSelectedScriptIndex < mScripts.size())
        {
          mTexturePipeline->AddLayer(mScripts[mSelectedScriptIndex]);
        }
      }
      ImGui::PopStyleColor(4);*/

      // ImGui::SameLine();
    }

    void
    RenderSettings()
    {
      // ImGui::Checkbox("Enabled", &mEnabled);
      //  ComboEnum("Blend mode", mBlendMode);

      // ImGui::SetNextItemWidth(200.f);
      // ImGui::SliderFloat("Contribution", &mContribution, 0.0F, 1.0F, "%.2F");

      for (auto& pair : mSettings)
      {
        std::string                    key = pair.first;
        std::variant<bool, int, float> value = pair.second;

        ImGui::SetNextItemWidth(200.f);

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

  public:
    ScriptNode()
    {
      mScripts = GetLuaScripts();
      setTitle("Lua Script");
      setStyle(ImFlow::NodeStyle::red());
      getStyle()->bg = IM_COL32(46, 52, 64, 255);
      getStyle()->header_bg = IM_COL32(180, 142, 173, 255);
      ImFlow::BaseNode::addIN<glm::vec2>(
        "Vector2D", glm::vec2(0), ImFlow::ConnectionFilter::SameType());
      ImFlow::BaseNode::addOUT<float>("Out", nullptr);
      //->behaviour([this]() { return getInVal<float>("In") + m_valB; });
    }

    void
    draw() override
    {
      // if (ImFlow::BaseNode::isSelected())
      //{
      //  Script drop down

      LuaScriptSelector();

      // Script settings

      // Preview
      // ImGui::InputInt("##ValB", &m_valB);
      // ImGui::Button("Hello");
      //}
    }
  };
}