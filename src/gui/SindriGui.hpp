#pragma once

#include "IGpuPreviewTexture.hpp"
#include "INodeEditorPanel.hpp"
#include "ISindriGui.hpp"
#include "ITextureBuffer.hpp"
#include "ITextureExporter.hpp"
#include "ITexturePipeline.hpp"
#include "ITexturePipelineExecutor.hpp"
#include "ITexturePreview.hpp"
#include "IVariablesPanel.hpp"
#include "IWindow.hpp"
#include "workflow_settings_panel/IWorkflowSettingsPanel.hpp"
#include <imgui.h>

namespace Sindri
{
  class SindriGui : public ISindriGui
  {
  private:
    std::shared_ptr<IWindow>                  mWindow;
    std::shared_ptr<ITexturePipeline>         mTexturePipeline;
    std::shared_ptr<ITextureExporter>         mExporter;
    std::shared_ptr<ITextureBuffer>           mTextureBuffer;
    std::shared_ptr<ITexturePipelineExecutor> mExecutor;
    std::shared_ptr<ITexturePreview>          mPreview;
    std::shared_ptr<IGpuPreviewTexture>       mGpuPreviewTexture;
    std::shared_ptr<INodeEditorPanel>         mNodeEditor;
    std::shared_ptr<IVariablesPanel>          mVariablesGui;
    std::shared_ptr<IWorkflowSettingsPanel>   mWorkflowSettingsPanel;

    // Basic ImGui Rendering functions
    void
    SetupImGuiStyles();

    void
    RenderImGui(float deltaTime);

    void
    RenderVariablesWindow(float deltaTime, ImVec2 position, ImVec2 size);

    void
    RenderWorkflowSettingsWindow(float deltaTime, ImVec2 position, ImVec2 size);

    void
    RenderNodeEditorWindow(float deltaTime, ImVec2 position, ImVec2 size);

  public:
    SindriGui(std::shared_ptr<IWindow>                  window,
              std::shared_ptr<IWorkflowSettingsPanel>   workflowSettingsPanel,
              std::shared_ptr<ITexturePipeline>         texturePipeline,
              std::shared_ptr<ITextureExporter>         exporter,
              std::shared_ptr<ITextureBuffer>           textureBuffer,
              std::shared_ptr<ITexturePreview>          preview,
              std::shared_ptr<IGpuPreviewTexture>       gpuPreviewTexture,
              std::shared_ptr<ITexturePipelineExecutor> texturePipelineExecutor,
              std::shared_ptr<INodeEditorPanel>         nodeEditor,
              std::shared_ptr<IVariablesPanel>          variablesGui);
    ~SindriGui() override = default;

    void
    Render(float deltaTime) override;
  };
}