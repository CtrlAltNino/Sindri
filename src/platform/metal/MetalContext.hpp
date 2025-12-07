#pragma once

#include "IGraphicsContext.hpp"
#include <SDL3/SDL.h>
#include <TargetConditionals.h>

namespace MTL
{
  class Device;
  class CommandQueue;
  class Drawable;
}

namespace Sindri
{
  /**
   * @brief A Metal implementation of the IGraphicsContext interface class
   */
  class MetalContext : public IGraphicsContext
  {
  private:
    SDL_Window*        mWindowHandle;
    SDL_MetalView      mMetalView = nullptr;
    void*              mMetalLayer = nullptr; // actually a CAMetalLayer*
    MTL::Device*       mDevice = nullptr;
    MTL::CommandQueue* mCommandQueue = nullptr;

  public:
    explicit MetalContext(SDL_Window* windowHandle);
    ~MetalContext() override;

    void
    Init() override;
    void
    SwapBuffers() override;

    // Optional getters if your renderer needs access
    MTL::Device*
    GetDevice() const
    {
      return mDevice;
    }
    MTL::CommandQueue*
    GetCommandQueue() const
    {
      return mCommandQueue;
    }
  };
}
