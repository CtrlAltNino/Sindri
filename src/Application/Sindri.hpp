#pragma once

#include "CompositionStack.hpp"
#include "NoiseGenerator.hpp"
#include "ProceduralTexture/ProceduralTexture.hpp"
#include "TextureExporter.hpp"
#include "TexturePreview.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <SDL3/SDL.h>
#include <filesystem>
#include <random>

namespace Sindri
{
  class SindriApp
  {
  private:
    SDL_Window*   mWindow = nullptr;
    SDL_GLContext mContext = nullptr;

    std::shared_ptr<TextureSettings> mTextureSettings = nullptr;

    std::shared_ptr<CompositionStack> mCompositionStack = nullptr;

    std::shared_ptr<ProceduralTexture> mTexture = nullptr;

    std::shared_ptr<TextureExporter> mExporter = nullptr;

    std::shared_ptr<TexturePreview> mPreview = nullptr;

    NoiseGenerator mNoiseGenerator;

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
    SindriApp();
    ~SindriApp();

    SindriApp(const SindriApp&) = delete;
    auto
    operator=(const SindriApp&) -> SindriApp& = delete;

    void
    Run();
  };
}