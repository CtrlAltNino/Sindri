#pragma once

#include "WorkflowSettings.hpp"

namespace Sindri
{
  class ITexturePipelineExecutor
  {
  public:
    virtual ~ITexturePipelineExecutor() = default;

    virtual void
    ExecutePipeline(std::shared_ptr<IWorkflowSettings> workflowSettings) = 0;

    virtual void
    CancelExecution() = 0;

    virtual auto
    IsRunning() -> bool = 0;

    virtual auto
    GetProgress() -> float = 0;
  };
}