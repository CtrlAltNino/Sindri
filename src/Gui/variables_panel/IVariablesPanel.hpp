#pragma once

namespace Sindri
{
  class IVariablesPanel
  {
  public:
    virtual ~IVariablesPanel() = default;
    virtual void
    Render() = 0;
  };
}