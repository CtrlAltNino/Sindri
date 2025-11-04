#include "pch.hpp"

#include "DecomposeVectorNode.hpp"
#include "DivideNode.hpp"
#include "LuaScriptNode.hpp"
#include "NegateNode.hpp"
#include "NodeEditor.hpp"
#include "OneMinusNode.hpp"
#include "OutputNode.hpp"
#include "PowNode.hpp"
#include "SqrtNode.hpp"
#include "SubtractNode.hpp"
#include "SumNode.hpp"
#include "UVNode.hpp"

namespace Sindri
{
  NodeEditor::NodeEditor(std::shared_ptr<IWorkflowSettings> workflowSettings)
    : mWorkflowSettings(std::move(workflowSettings))
    , BaseNode()
  {
    float d = 1500;
    float r = 500;
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

          if (ImGui::BeginMenu("Vector Operations"))
          {
            if (ImGui::MenuItem("Add Vectors"))
            {
              // mINF.addNode<>(ImGui::GetMousePos());
            }
            if (ImGui::MenuItem("Compose Vectors"))
            {
            }
            if (ImGui::MenuItem("Cross Product"))
            {
            }
            if (ImGui::MenuItem("Decompose Vector"))
            {
              mINF.addNode<DecomposeVectorNode>(ImGui::GetMousePos());
            }
            if (ImGui::MenuItem("Divide Vectors"))
            {
            }
            if (ImGui::MenuItem("Dot Product"))
            {
            }
            if (ImGui::MenuItem("Compute Length"))
            {
            }
            if (ImGui::MenuItem("Multiply Vectors"))
            {
            }
            if (ImGui::MenuItem("Subtract Vectors"))
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

    UpdateUVNode();
    UpdateOutputNode();
    mWorkflowSettings->RegisterObserver(this);
  }

  NodeEditor::~NodeEditor()
  {
    mWorkflowSettings->UnregisterObserver(this);
  }

  void
  NodeEditor::SetSize(ImVec2 size)
  {
    mINF.setSize(size);
  }

  void
  NodeEditor::Draw()
  {
    mINF.update();
  }

  void
  NodeEditor::UpdateUVNode()
  {
    if (!mUVNode)
    {
      mUVNode = AddNode<UVNode>({ 170, 300 });
    }

    mUVNode->setup(mWorkflowSettings->GetDimensions());
  }

  void
  NodeEditor::UpdateOutputNode()
  {
    if (!mOutputNode)
    {
      mOutputNode = AddNode<OutputNode>({ 570, 300 });
    }

    // setup output node
  }

  auto
  NodeEditor::GetRootNode() -> ImFlow::ImNodeFlow*
  {
    return &mINF;
  }

  void
  NodeEditor::OnDimensionsChanged()
  {
    UpdateUVNode();
  }

  void
  NodeEditor::OnChannelCountChanged()
  {
    UpdateOutputNode();
  }

  void
  NodeEditor::OnSeedChanged()
  {
  }
}