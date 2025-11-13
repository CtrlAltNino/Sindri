#pragma once

#include "DecomposeVectorNode.hpp"
#include "DivideNode.hpp"
#include "INodeEditorPanel.hpp"
#include "IVariableRegistry.hpp"
#include "IWorkflowSettingsPanel.hpp"
#include "LuaScriptNode.hpp"
#include "MultiplyNode.hpp"
#include "NegateNode.hpp"
#include "NodeEditor.hpp"
#include "OneMinusNode.hpp"
#include "OutputNode.hpp"
#include "PowNode.hpp"
#include "SqrtNode.hpp"
#include "SubtractNode.hpp"
#include "SumNode.hpp"
#include "TextureTypes.hpp"
#include "UVNode.hpp"
#include "WorkflowSettings.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>


namespace Sindri
{
  class NodeEditorPanel : public INodeEditorPanel
  {
  private:
    /* Create a node editor with width and height */
    std::shared_ptr<INodeEditor>       mNodeEditor;
    std::shared_ptr<IVariableRegistry> mVariableRegistry;
    std::shared_ptr<IWorkflowSettings> mWorkflowSettings;

  public:
    NodeEditorPanel(std::shared_ptr<INodeEditor>       nodeEditor,
                    std::shared_ptr<IVariableRegistry> variableRegistry,
                    std::shared_ptr<IWorkflowSettings> workflowSettings);
    ~NodeEditorPanel() override;

    void
    Render() override;
  };
}