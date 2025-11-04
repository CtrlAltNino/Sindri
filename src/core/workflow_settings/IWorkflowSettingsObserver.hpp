#pragma once

namespace Sindri
{
  class IWorkflowSettingsObserver
  {
  public:
    virtual ~IWorkflowSettingsObserver() = default;

    virtual void
    OnDimensionsChanged() = 0;

    virtual void
    OnChannelCountChanged() = 0;

    virtual void
    OnSeedChanged() = 0;
  };
}