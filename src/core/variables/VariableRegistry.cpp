#include "pch.hpp"
#include <algorithm>
#include <string>

#include "VariableRegistry.hpp"

namespace Sindri
{
  auto
  VariableRegistry::Create(const std::string&       name,
                           VarKind                  kind,
                           const NodeVariableValue& initialValue)
    -> VariableDef&
  {
    VariableDef newVariable{
      .name = name,
      .kind = kind,
      .value = initialValue,
    };

    mVariables[newVariable.name] = newVariable; // cheap non‑owning lookup table
    return mVariables[newVariable.name];
  }

  auto
  VariableRegistry::GetByName(const std::string& name) -> VariableDef*
  {
    return mVariables.contains(name) ? &mVariables[name] : nullptr;
  }

  // ---------- Mutation ----------
  auto
  VariableRegistry::Rename(const std::string& oldName,
                           const std::string& newName) -> bool
  {
    if (auto* v = GetByName(oldName))
    {
      v->name = newName;
      return true;
    }

    return false;
  }

  void
  VariableRegistry::Erase(const std::string& name)
  {

    for (auto it = mVariables.begin(); it != mVariables.end();)
    {
      if (it->first == name)
      {
        it = mVariables.erase(it);
      }
      else
      {
        ++it;
      }
    }
  }

  // ---------- Iteration ----------
  auto
  VariableRegistry::All() -> std::unordered_map<std::string, VariableDef>&
  {
    return mVariables;
  }
}