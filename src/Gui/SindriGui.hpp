#pragma once

#include "Gui/ISindriGui.hpp"
#include "IGpuPreviewTexture.hpp"
#include "ITextureBuffer.hpp"
#include "ITextureExporter.hpp"
#include "ITexturePipeline.hpp"
#include "ITexturePipelineExecutor.hpp"
#include "ITexturePreview.hpp"
#include "IWindow.hpp"
#include "NodeEditor/INodeEditor.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <imgui.h>

namespace Sindri
{
  class SindriGui : public ISindriGui
  {
  private:
    std::shared_ptr<IWindow> mWindow;

    std::shared_ptr<TextureSettings> mTextureSettings;

    std::shared_ptr<ITexturePipeline> mTexturePipeline;

    std::shared_ptr<ITextureExporter> mExporter;

    std::shared_ptr<ITextureBuffer> mTextureBuffer;

    std::shared_ptr<ITexturePipelineExecutor> mExecutor;

    std::shared_ptr<ITexturePreview> mPreview;

    std::shared_ptr<IGpuPreviewTexture> mGpuPreviewTexture;

    std::shared_ptr<INodeEditor> mNodeEditor;

    std::random_device mRandomDevice;

    float mFps = 0.0F;
    float mMsPerFrame = 0.0F;

    int                                mSelectedScriptIndex = 0;
    std::vector<std::filesystem::path> mScripts;

    // Basic ImGui Rendering functions

    void
    SetupImGuiStyles();

    void
    RenderImGui(float deltaTime);

    void
    RenderSettingsWindow(float deltaTime, ImVec2 position, ImVec2 size);

    void
    RenderPreviewWindow(float deltaTime, ImVec2 position, ImVec2 size);

    void
    RenderNodeEditorWindow(float deltaTime, ImVec2 position, ImVec2 size);

    // Helper
    auto
    GetLuaScripts() -> std::vector<std::filesystem::path>;

    void
    LuaScriptSelector();

    void
    GenerateTexture();

  public:
    SindriGui(std::shared_ptr<IWindow>                  window,
              std::shared_ptr<TextureSettings>          textureSettings,
              std::shared_ptr<ITexturePipeline>         texturePipeline,
              std::shared_ptr<ITextureExporter>         exporter,
              std::shared_ptr<ITextureBuffer>           textureBuffer,
              std::shared_ptr<ITexturePreview>          preview,
              std::shared_ptr<IGpuPreviewTexture>       gpuPreviewTexture,
              std::shared_ptr<ITexturePipelineExecutor> texturePipelineExecutor,
              std::shared_ptr<INodeEditor>              nodeEditor);
    ~SindriGui() override = default;

    void
    Render(float deltaTime) override;
  };
}