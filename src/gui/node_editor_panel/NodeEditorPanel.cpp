#include "pch.hpp"

#include "NodeEditorPanel.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>
#include <utility>

namespace Sindri
{
  NodeEditorPanel::NodeEditorPanel(
    std::shared_ptr<INodeEditor>       nodeEditor,
    std::shared_ptr<IVariableRegistry> variableRegistry,
    std::shared_ptr<IWorkflowSettings> workflowSettings)
    : mVariableRegistry(std::move(variableRegistry))
    , mWorkflowSettings(std::move(workflowSettings))
    , mNodeEditor(std::move(nodeEditor))
  {
  }

  NodeEditorPanel::~NodeEditorPanel() {}

  void
  NodeEditorPanel::Render()
  {
    mNodeEditor->SetSize(ImGui::GetContentRegionAvail());
    mNodeEditor->Draw();
  }
}