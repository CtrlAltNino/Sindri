#include "pch.hpp"

#include "NodeEditor.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>

namespace Sindri
{
  NodeEditor::NodeEditor()
    : mNodeEditor(1500, 500)
  {
  }

  NodeEditor::~NodeEditor() {}

  void
  NodeEditor::Render()
  {
    mNodeEditor.set_size(ImGui::GetContentRegionAvail());
    mNodeEditor.draw();
  }
}