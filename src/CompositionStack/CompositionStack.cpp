#include "pch.hpp"

#include "CompositionStack.hpp"
#include "StackEntry.hpp"
#include <imgui.h>

namespace Sindri
{
  CompositionStack::CompositionStack() {}

  void
  CompositionStack::Add(std::filesystem::path luaScriptPath)
  {
    mStack.push_back(StackEntry(luaScriptPath));
  }

  void
  CompositionStack::Remove(uint32_t index)
  {
    // std::erase(mStack, index);
    mStack.erase(mStack.begin() + index);
  }

  void
  CompositionStack::RenderSettings()
  {
    int  index = 0;
    auto deleteIterator = mStack.end();
    for (auto it = mStack.begin(); it != mStack.end();)
    {
      ImGui::PushID(index); // Start a unique ID scope
      {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
        ImGuiChildFlags  childFlags = ImGuiChildFlags_AutoResizeY |
                                     ImGuiChildFlags_AutoResizeX |
                                     ImGuiChildFlags_Borders;
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
        ImGui::BeginChild("ChildR", ImVec2(0, 0), childFlags, windowFlags);
        ImGui::Text(
          "%s",
          std::string(std::to_string(index + 1) + ". " + it->GetName())
            .c_str());
        ImGui::Separator();
        ImGui::Spacing();
        it->RenderSettings();
        if (ImGui::Button("Delete"))
        {
          // Remove(index);
          // it = mStack.erase(it);
          deleteIterator = it;
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
        index++;
        ++it;
      }
      ImGui::PopID();
    }

    if (deleteIterator != mStack.end())
    {
      mStack.erase(deleteIterator);
    }
  }

  auto
  CompositionStack::GetEntries() -> std::vector<StackEntry>&
  {
    return mStack;
  }
}