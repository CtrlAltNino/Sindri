#include "pch.hpp"

#include "ImGuiHelper.hpp"
#include "UVNode.hpp"
#include "VariableNode.hpp"
#include "VariablesPanel.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <utility>

namespace Sindri
{
  VariablesPanel::VariablesPanel(
    std::shared_ptr<IVariableRegistry> variableRegistry,
    std::shared_ptr<INodeEditor>       nodeEditor)
    : mVariableRegistry(std::move(variableRegistry))
    , mNodeEditor(std::move(nodeEditor))
  {
  }

  void
  VariablesPanel::Render()
  {
    // TODO: Draw all variables
    for (auto& var : mVariableRegistry->All())
    {
      switch (var.second.kind)
      {
        case VarKind::Float:
          {
            auto label = var.first;
            label += " (Float)";
            float current = std::get<float>(var.second.value);
            if (ImGui::InputFloat(label.c_str(), &current))
            {
              var.second.value = current;
            }
            break;
          }
        case VarKind::Int:
          {
            auto label = var.first;
            label += " (Int)";
            int current = std::get<int>(var.second.value);
            if (ImGui::InputInt(label.c_str(), &current))
            {
              var.second.value = current;
            }
            break;
          }
        case VarKind::Vec2:
          {
            auto label = var.first;
            label += " (Vec2)";
            glm::vec2 current = std::get<glm::vec2>(var.second.value);
            if (ImGui::InputFloat2(label.c_str(), glm::value_ptr(current)))
            {
              var.second.value = current;
            }
            break;
          }
        case VarKind::Vec3:
          {
            auto label = var.first;
            label += " (Vec3)";
            glm::vec3 current = std::get<glm::vec3>(var.second.value);
            if (ImGui::InputFloat3(label.c_str(), glm::value_ptr(current)))
            {
              var.second.value = current;
            }
            break;
          }
        case VarKind::Vec4:
          {
            auto label = var.first;
            label += " (Vec4)";
            glm::vec4 current = std::get<glm::vec4>(var.second.value);
            if (ImGui::InputFloat4(label.c_str(), glm::value_ptr(current)))
            {
              var.second.value = current;
            }
            break;
          }
      }

      ImGui::SameLine();
      if (ImGui::Button("+"))
      {
        mNodeEditor->AddNode<VariableNode>(
          { 170, 300 }, mVariableRegistry->GetByName(var.first));
      }
    }

    // TODO: Draw add variable
    ImGui::SeparatorText("Add new variable");
    InputTextString("Name", mNewVarData.Name);
    // ImGui::SameLine();
    ComboEnum("Type", mNewVarData.Kind);
    // ImGui::SameLine();
    if (ImGui::Button("Add"))
    {
      switch (mNewVarData.Kind)
      {
        case VarKind::Float:
          mVariableRegistry->Create(mNewVarData.Name, mNewVarData.Kind, 0.0F);
          break;
        case VarKind::Int:
          mVariableRegistry->Create(mNewVarData.Name, mNewVarData.Kind, 0);
          break;
        case VarKind::Vec2:
          mVariableRegistry->Create(
            mNewVarData.Name, mNewVarData.Kind, glm::vec2(0.0F, 0.0F));
          break;
        case VarKind::Vec3:
          mVariableRegistry->Create(
            mNewVarData.Name, mNewVarData.Kind, glm::vec3(0.0F, 0.0F, 0.0F));
          break;
        case VarKind::Vec4:
          mVariableRegistry->Create(mNewVarData.Name,
                                    mNewVarData.Kind,
                                    glm::vec4(0.0F, 0.0F, 0.0F, 0.0F));
          break;
      }
    }
  }
}