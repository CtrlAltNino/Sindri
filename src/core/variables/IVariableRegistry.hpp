#pragma once

#include "Variable.hpp"

namespace Sindri
{
  class IVariableRegistry
  {
  public:
    virtual ~IVariableRegistry() = default;
    // CRUD ---------------------------------------------------------
    virtual auto
    Create(const std::string&       name,
           VarKind                  kind,
           const NodeVariableValue& initialValue) -> VariableDef& = 0;

    /**
     * @brief Get's a variable by it's name
     *
     * @param name Name of the variable
     * @return Pointer to the variable struct
     */
    virtual auto
    GetByName(const std::string& name)
      -> VariableDef* = 0; // convenience lookup

    /**
     * @brief Tries to rename a variable
     *
     * @param oldName Old name of the variable
     * @param newName New name of the variable
     * @return true Successful rename
     * @return false Failed rename
     */
    virtual auto
    Rename(const std::string& oldName, const std::string& newName) -> bool = 0;

    /**
     * @brief Removes a variable
     *
     * @param name Name of the variable to erase
     */
    virtual void
    Erase(const std::string& name) = 0;

    // Enumeration --------------------------------------------------
    [[nodiscard]] virtual auto
    All() -> std::unordered_map<std::string, VariableDef>& = 0;
  };
}