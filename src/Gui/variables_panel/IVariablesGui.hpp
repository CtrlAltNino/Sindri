#pragma once

namespace Sindri
{
  class IVariablesGui
  {
  public:
    virtual ~IVariablesGui() = default;
    virtual void
    Render() = 0;
  };
}