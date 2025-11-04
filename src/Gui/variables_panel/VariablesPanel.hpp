#pragma once
#include "IVariableRegistry.hpp"
#include "IVariablesPanel.hpp"
#include "NodeEditor.hpp"

namespace Sindri
{
  struct NewVariableData
  {
    std::string Name;
    VarKind     Kind = VarKind::Float;
  };

  class VariablesPanel : public IVariablesPanel
  {
  private:
    std::shared_ptr<IVariableRegistry> mVariableRegistry;
    NewVariableData                    mNewVarData;
    std::shared_ptr<INodeEditor>       mNodeEditor;

  public:
    VariablesPanel(std::shared_ptr<IVariableRegistry> variableRegistry,
                   std::shared_ptr<INodeEditor>       nodeEditor);

    void
    Render() override;
  };
}