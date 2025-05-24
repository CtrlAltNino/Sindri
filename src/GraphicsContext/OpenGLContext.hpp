#pragma once

#include "IGraphicsContext.hpp"
#include <SDL3/SDL.h>

namespace Sindri
{
  class OpenGLContext : public IGraphicsContext
  {
  private:
    SDL_Window*   mWindowHandle;
    SDL_GLContext mContext = nullptr;

  public:
    explicit OpenGLContext(SDL_Window* windowHandle);
    ~OpenGLContext() override;

    /**
     * @brief Initializes the the graphics context
     *
     */
    void
    Init() override;

    /**
     * @brief Swaps the buffers
     *
     */
    void
    SwapBuffers() override;
  };
}