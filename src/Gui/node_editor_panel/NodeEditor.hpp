#pragma once

#include "DecomposeVectorNode.hpp"
#include "DivideNode.hpp"
#include "INodeEditor.hpp"
#include "IVariableRegistry.hpp"
#include "LuaScriptNode.hpp"
#include "MultiplyNode.hpp"
#include "NegateNode.hpp"
#include "OneMinusNode.hpp"
#include "OutputNode.hpp"
#include "PowNode.hpp"
#include "SqrtNode.hpp"
#include "SubtractNode.hpp"
#include "SumNode.hpp"
#include "UVNode.hpp"
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

            /*if (ImGui::Selectable("Add variable node"))
            {
            }*/

            if (ImGui::BeginMenu("Arithmetic operations"))
            {
              if (ImGui::MenuItem("Sum"))
              {
                mINF.addNode<SumNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Subtract"))
              {
                mINF.addNode<SubtractNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Divide"))
              {
                mINF.addNode<DivideNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Multiply"))
              {
                mINF.addNode<SumNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Negate"))
              {
                mINF.addNode<NegateNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("OneMinus"))
              {
                mINF.addNode<OneMinusNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Pow"))
              {
                mINF.addNode<PowNode>(ImGui::GetMousePos());
              }
              if (ImGui::MenuItem("Sqrt"))
              {
                mINF.addNode<SqrtNode>(ImGui::GetMousePos());
              }
              ImGui::EndMenu();
            }

            /*if (ImGui::BeingMenu("Vector Operations"))
            {
              if (ImGui::MenuItem("Sum"))
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
            }*/
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
    ImNodeEditor                       mNodeEditor;
    std::shared_ptr<IVariableRegistry> mVariableRegistry;

  public:
    NodeEditor(std::shared_ptr<IVariableRegistry> variableRegistry);
    ~NodeEditor() override;

    void
    Render() override;

    void
    AddVariableNode(std::string identifier) override;
  };
}