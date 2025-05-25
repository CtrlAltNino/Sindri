#include "pch.hpp"

#include "NoiseLayer/INoiseLayer.hpp"
#include "TexturePipeline.hpp"
#include <imgui.h>

namespace Sindri
{
  TexturePipeline::TexturePipeline(
    std::shared_ptr<INoiseLayerFactory> noiseLayerFactory)
    : mNoiseLayerFactory(std::move(noiseLayerFactory))
  {
  }

  void
  TexturePipeline::AddLayer(std::filesystem::path luaScriptPath)
  {
    mNoiseLayers.emplace_back(mNoiseLayerFactory->Create(luaScriptPath));
  }

  void
  TexturePipeline::RemoveLayer(uint32_t index)
  {
    mNoiseLayers.erase(mNoiseLayers.begin() + index);
  }

  void
  TexturePipeline::MoveLayer(uint32_t fromIndex, uint32_t toIndex)
  {
    // TODO: Implement
  }

  void
  TexturePipeline::RenderAllSettings()
  {
    int  index = 0;
    auto deleteIterator = mNoiseLayers.end();
    for (auto it = mNoiseLayers.begin(); it != mNoiseLayers.end();)
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
          std::string(std::to_string(index + 1) + ". " + it->get()->GetName())
            .c_str());
        ImGui::Separator();
        ImGui::Spacing();
        it->get()->RenderSettings();
        if (ImGui::Button("Reload"))
        {
          it->get()->ReloadScriptFile();
        }

        ImGui::SameLine();

        if (ImGui::Button("Delete"))
        {
          deleteIterator = it;
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
        index++;
        ++it;
      }
      ImGui::PopID();
    }

    if (deleteIterator != mNoiseLayers.end())
    {
      mNoiseLayers.erase(deleteIterator);
    }
  }

  auto
  TexturePipeline::GetLayers() -> std::vector<std::shared_ptr<INoiseLayer>>&
  {
    return mNoiseLayers;
  }
}