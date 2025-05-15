#pragma once

#include "NoiseGenerator.hpp"
#include "ProceduralTexture/ProceduralTexture.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <SDL3/SDL.h>
#include <random>

namespace Sindri
{
  class SindriApp
  {
  private:
    SDL_Window*   mWindow = nullptr;
    SDL_GLContext mContext = nullptr;

    TextureSettings mTextureSettings;

    NoiseGenerator mNoiseGenerator;

    std::shared_ptr<ProceduralTexture> mTexture = nullptr;

    bool mRunning = false;

    std::random_device mRandomDevice;

    int mWidth = 1280;
    int mHeight = 720;
    int mCurrentWindowWidth = 1280;
    int mCurrentWindowHeight = 720;

    bool mVsync = true;

    float       mFps = 0.0F;
    float       mMsPerFrame = 0.0F;
    std::string mTitle = "Sindri";

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
    MainWindow();

    void
    GenerateTexture();

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