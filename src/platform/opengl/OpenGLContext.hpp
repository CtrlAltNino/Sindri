#pragma once

#include "IGraphicsContext.hpp"
#include <SDL3/SDL.h>

namespace Sindri
{
  /**
   * @brief An OpenGL implementation of the IGraphicsContext interface class
   *
   */
  class OpenGLContext : public IGraphicsContext
  {
  private:
    SDL_Window*   mWindowHandle;
    SDL_GLContext mContext = nullptr;

  public:
    explicit OpenGLContext(SDL_Window* windowHandle);
    ~OpenGLContext() override;

    /// @copydoc IGraphicsContext::Init
    void
    Init() override;

    /// @copydoc IGraphicsContext::SwapBuffers
    void
    SwapBuffers() override;

    void
    SetVsync(bool vsync) override;

    auto
    GetContextHandle() -> SDL_GLContext;
  };
}