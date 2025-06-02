#pragma once

#include "INodeEditor.hpp"
#include "Nodes/DecomposeNode.hpp"
#include "Nodes/OutputNode.hpp"
#include "Nodes/ScriptNode.hpp"
#include "Nodes/UVNode.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>

namespace Sindri
{
  /* Node editor that sets up the grid to place nodes */
  struct ImNodeEditor : ImFlow::BaseNode
  {
    ImFlow::ImNodeFlow mINF;
    ImNodeEditor(float d, std::size_t r)
      : BaseNode()
    {
      mINF.setSize({ d, d });
      mINF.getStyle().colors.grid = IM_COL32(59, 66, 82, 196);
      mINF.getStyle().colors.subGrid = IM_COL32(76, 86, 106, 64);
      // mINF.getStyle().colors.background = IM_COL32(255, 255, 255, 0);
      mINF.getGrid().config().color = IM_COL32(37, 41, 51, 255);

      mINF.rightClickPopUpContent(
        [this](BaseNode* node)
        {
          /* omitted */
          if (node == nullptr)
          {
            // ImGui::Text("Background right click");
            if (ImGui::Selectable("Add script node"))
            {
              mINF.addNode<ScriptNode>(ImGui::GetMousePos());
            }

            if (ImGui::Selectable("Add variable node"))
            {
            }

            if (ImGui::BeginMenu("Add math node"))
            {
              if (ImGui::MenuItem("Add"))
              {
              }
              if (ImGui::MenuItem("Subtract"))
              {
              }
              if (ImGui::MenuItem("Divide"))
              {
              }
              if (ImGui::MenuItem("Multiply"))
              {
              }
              ImGui::EndMenu();
            }
          }
          else
          {
            if (ImGui::Selectable("Duplicate"))
            {
              // TODO: Implement
            }

            if (ImGui::Selectable("Delete"))
            {
              // TODO: Implement
              node->destroy();
            }
          }
        });

      if (r > 0)
      {
        mINF.addNode<Texture2DCoordNode>({ 170, 300 });
        mINF.addNode<DecomposeVec2Node>({ 380, 300 });
        mINF.addNode<OutputNode>({ 570, 300 });
      }
    }

    void
    set_size(ImVec2 d)
    {
      mINF.setSize(d);
    }

    void
    draw() override
    {
      mINF.update();
    }
  };

  class NodeEditor : public INodeEditor
  {
  private:
    /* Create a node editor with width and height */
    ImNodeEditor mNodeEditor;

  public:
    NodeEditor();
    ~NodeEditor() override;

    void
    Render() override;
  };
}