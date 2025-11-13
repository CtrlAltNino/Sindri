#pragma once

#include "IWorkflowSettings.hpp"
#include "IWorkflowSettingsPanel.hpp"

namespace Sindri
{
  class WorkflowSettingsPanel : public IWorkflowSettingsPanel
  {
  private:
    std::shared_ptr<IWorkflowSettings> mWorkflowSettings;

    std::random_device mRandomDevice;

  public:
    WorkflowSettingsPanel(std::shared_ptr<IWorkflowSettings> workflowSettings);

    void
    Render() override;
  };
}