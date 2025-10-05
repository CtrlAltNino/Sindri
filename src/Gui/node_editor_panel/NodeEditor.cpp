#include "pch.hpp"

#include "NodeEditor.hpp"
#include "VariableNode.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>
#include <utility>

namespace Sindri
{
  NodeEditor::NodeEditor(std::shared_ptr<IVariableRegistry> variableRegistry)
    : mVariableRegistry(std::move(variableRegistry))
    , mNodeEditor(1500, 500)
  {
  }

  NodeEditor::~NodeEditor() {}

  void
  NodeEditor::Render()
  {
    mNodeEditor.set_size(ImGui::GetContentRegionAvail());
    mNodeEditor.draw();
  }

  void
  NodeEditor::AddVariableNode(std::string identifier)
  {
    mNodeEditor.mINF.addNode<VariableNode>(
      { 170, 300 }, mVariableRegistry->GetByName((identifier)));
  }
}