#pragma once

#include "IGraphicsContext.hpp"
#include <SDL3/SDL.h>
#include <TargetConditionals.h>
#include <metal-cpp/Metal/Metal.hpp>
#include <metal-cpp/QuartzCore/CAMetalLayer.hpp>

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
    CA::MetalLayer*    mMetalLayer = nullptr; // actually a CAMetalLayer*
    MTL::Device*       mDevice = nullptr;
    MTL::CommandQueue* mCommandQueue = nullptr;

  public:
    explicit MetalContext(SDL_Window* windowHandle);
    ~MetalContext() override;

    void
    Init() override;

    void
    SwapBuffers() override;

    void
    SetVsync(bool vsync) override;

    // Called each frame
    auto
    BeginFrame() -> MTL::CommandBuffer*;

    auto
    CreateImGuiRenderPass(CA::MetalDrawable* drawable)
      -> MTL::RenderPassDescriptor*;
    void
    EndFrame(MTL::CommandBuffer* cmdBuffer);

    // Optional getters if your renderer needs access
    [[nodiscard]] auto
    GetDevice() const -> MTL::Device*
    {
      return mDevice;
    }

    [[nodiscard]] auto
    GetCommandQueue() const -> MTL::CommandQueue*
    {
      return mCommandQueue;
    }

    [[nodiscard]] auto
    GetMetalLayer() const -> CA::MetalLayer*
    {
      return mMetalLayer;
    }
  };
}
