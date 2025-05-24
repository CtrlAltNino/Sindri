#pragma once

#include "IGpuPreviewTexture.hpp"
#include "ISindriGui.hpp"
#include "ITextureExporter.hpp"
#include "ITexturePreview.hpp"
#include "IWindow.hpp"
#include "ProceduralTexture/ProceduralTexture.hpp"
#include "TexturePipeline/ITexturePipeline.hpp"
#include "TexturePipelineExecutor/ITexturePipelineExecutor.hpp"
#include "TexturePreview.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <SDL3/SDL.h>
#include <filesystem>
#include <random>

namespace Sindri
{
  class Sindri
  {
  private:
    // SDL_Window*   mWindow = nullptr;
    // SDL_GLContext mContext = nullptr;

    std::shared_ptr<ISindriGui> mGui = nullptr;

    std::shared_ptr<IWindow> mWindow = nullptr;

    std::shared_ptr<ITextureExporter> mExporter = nullptr;

    std::shared_ptr<ITexturePreview> mPreview = nullptr;

    std::shared_ptr<ITexturePipelineExecutor> mPipelineExecutor;

    std::shared_ptr<IGpuPreviewTexture> mGpuPreviewTexture;

    // bool mRunning = false;

    // int mSelectedScriptIndex = 0;
    // std::vector<std::filesystem::path> mScripts;

    // bool mVsync = true;

    // float       mFps = 0.0F;
    // float       mMsPerFrame = 0.0F;
    // std::string mTitle = "Sindri";

    // auto
    // Init() -> bool; // Internal init
    // void
    // Shutdown(); // Internal shutdown
    void
    MainLoop(); // Internal loop

    // void
    // HandleEvents(); // Poll input events
    // void
    // Render();

    // void
    // MainWindow(float deltaTime);

    // void
    // GenerateTexture();

    // auto
    // GetLuaScripts() -> std::vector<std::filesystem::path>;

    // void
    // LuaScriptSelector();

  public:
    Sindri(std::shared_ptr<ISindriGui>         gui,
           std::shared_ptr<IWindow>            window,
           std::shared_ptr<ITexturePreview>    preview,
           std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture);
    ~Sindri();

    Sindri(const Sindri&) = delete;
    auto
    operator=(const Sindri&) -> Sindri& = delete;

    void
    Run();
  };
}