#pragma once

namespace Sindri
{
  class IWorkflowSettingsPanel
  {
  public:
    virtual ~IWorkflowSettingsPanel() = default;
    virtual void
    Render() = 0;
  };
}