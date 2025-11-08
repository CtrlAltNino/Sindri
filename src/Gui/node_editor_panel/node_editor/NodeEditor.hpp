#pragma once

#include "IGpuPreviewTextureFactory.hpp"
#include "INodeEditor.hpp"
#include "IWorkflowSettingsObserver.hpp"
#include "OutputNode.hpp"
#include "UVNode.hpp"
#include <ImNodeFlow.h>
#include <imgui.h>

namespace Sindri
{
  /* Node editor that sets up the grid to place nodes */
  class NodeEditor
    : public INodeEditor
    , public ImFlow::BaseNode
    , public IWorkflowSettingsObserver
  {
  private:
    ImFlow::ImNodeFlow                         mINF;
    std::shared_ptr<UVNode>                    mUVNode;
    std::shared_ptr<OutputNode>                mOutputNode;
    std::shared_ptr<IWorkflowSettings>         mWorkflowSettings;
    std::shared_ptr<IGpuPreviewTextureFactory> mPreviewTextureFactory;

    void
    UpdateUVNode();

    void
    UpdateOutputNode();

  public:
    NodeEditor(
      std::shared_ptr<IWorkflowSettings>         workflowSettings,
      std::shared_ptr<IGpuPreviewTextureFactory> previewTextureFactory);
    ~NodeEditor() override;

    void
    SetSize(ImVec2 size) override;

    auto
    GetRootNode() -> ImFlow::ImNodeFlow* override;

    void
    Draw() override;

    void
    OnDimensionsChanged() override;

    void
    OnChannelCountChanged() override;

    void
    OnSeedChanged() override;
  };
}