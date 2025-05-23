#pragma once

#include "ProceduralTexture/ProceduralTexture.hpp"
#include "TextureExporter.hpp"
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
    SDL_Window*   mWindow = nullptr;
    SDL_GLContext mContext = nullptr;

    TextureSettings mTextureSettings;

    std::shared_ptr<ITexturePipeline> mCompositionStack = nullptr;

    // std::shared_ptr<ITextureBuffer> mTextureBuffer = nullptr;

    std::shared_ptr<TextureExporter> mExporter = nullptr;

    std::shared_ptr<TexturePreview> mPreview = nullptr;

    std::shared_ptr<ITexturePipelineExecutor> mPipelineExecutor;

    bool mRunning = false;

    std::random_device mRandomDevice;

    int mWidth = 1280;
    int mHeight = 720;
    int mCurrentWindowWidth = 1280;
    int mCurrentWindowHeight = 720;

    int mSelectedScriptIndex = 0;

    bool mVsync = true;

    float       mFps = 0.0F;
    float       mMsPerFrame = 0.0F;
    std::string mTitle = "Sindri";

    std::vector<std::filesystem::path> mScripts;

    auto
    Init() -> bool; // Internal init
    void
    Shutdown(); // Internal shutdown
    void
    MainLoop(); // Internal loop

    void
    HandleEvents(); // Poll input events
    void
    Render();

    void
    MainWindow(float deltaTime);

    void
    GenerateTexture();

    auto
    GetLuaScripts() -> std::vector<std::filesystem::path>;

    void
    LuaScriptSelector();

  public:
    Sindri(std::shared_ptr<ITexturePipeline> compositionStack);
    ~Sindri();

    Sindri(const Sindri&) = delete;
    auto
    operator=(const Sindri&) -> Sindri& = delete;

    void
    Run();
  };
}