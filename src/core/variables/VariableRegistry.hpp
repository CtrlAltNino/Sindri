#pragma once
#include "IVariableRegistry.hpp"

namespace Sindri
{
  class VariableRegistry : public IVariableRegistry
  {
  private:
    std::unordered_map<std::string, VariableDef> mVariables;

  public:
    ~VariableRegistry() override = default;

    // CRUD ---------------------------------------------------------
    auto
    Create(const std::string&       name,
           VarKind                  kind,
           const NodeVariableValue& initialValue) -> VariableDef& override;

    auto
    GetByName(const std::string& name)
      -> VariableDef* override; // convenience lookup

    auto
    Rename(const std::string& oldName, const std::string& newName)
      -> bool override;

    void
    Erase(const std::string& name) override;

    // Enumeration --------------------------------------------------
    [[nodiscard]] auto
    All() -> std::unordered_map<std::string, VariableDef>& override;
  };
}