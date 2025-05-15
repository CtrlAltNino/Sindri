#pragma once

#include <SDL3/SDL.h>

namespace Sindri
{
  class SindriApp
  {
  private:
    SDL_Window*   m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    bool m_Running = false;

    int m_Width = 1280;
    int m_Height = 720;

    float       mFps = 0.0F;
    float       mMsPerFrame = 0.0F;
    std::string m_Title = "Sindri";

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