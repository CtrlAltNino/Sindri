#pragma once

#include "INodeEditor.hpp"
#include "IVariableRegistry.hpp"
#include "IVariablesGui.hpp"

namespace Sindri
{
  struct NewVariableData
  {
    std::string Name;
    VarKind     Kind = VarKind::Float;
  };

  class VariablesGui : public IVariablesGui
  {
  private:
    std::shared_ptr<IVariableRegistry> mVariableRegistry;
    NewVariableData                    mNewVarData;
    std::shared_ptr<INodeEditor>       mNodeEditor;

  public:
    VariablesGui(std::shared_ptr<IVariableRegistry> variableRegistry,
                 std::shared_ptr<INodeEditor>       nodeEditor);

    void
    Render() override;
  };
}