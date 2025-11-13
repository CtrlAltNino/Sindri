#include "pch.hpp"
#include "MetalContext.hpp"

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

namespace Sindri
{
  MetalContext::MetalContext(SDL_Window* windowHandle)
    : mWindowHandle(windowHandle)
  {
  }

  MetalContext::~MetalContext()
  {
    if (mCommandQueue)
      mCommandQueue->release();

    if (mDevice)
      mDevice->release();

    if (mMetalView)
      SDL_Metal_DestroyView(mMetalView);
  }

  void MetalContext::Init()
  {
    // Create Metal view
    mMetalView = SDL_Metal_CreateView(mWindowHandle);
    mMetalLayer = SDL_Metal_GetLayer(mMetalView);

    if (!mMetalLayer)
    {
      std::cerr << "Failed to get Metal layer from SDL window." << std::endl;
      return;
    }

    // Create Metal device
    mDevice = MTL::CreateSystemDefaultDevice();
    if (!mDevice)
    {
      std::cerr << "Failed to create Metal device." << std::endl;
      return;
    }

    // Configure the CAMetalLayer
    CAMetalLayer* layer = static_cast<CAMetalLayer*>(mMetalLayer);
    layer.device = (__bridge id<MTLDevice>)mDevice->retained_id();
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.framebufferOnly = YES;

    // Create a command queue
    mCommandQueue = mDevice->newCommandQueue();

    if (!mCommandQueue)
    {
      std::cerr << "Failed to create Metal command queue." << std::endl;
      return;
    }
  }

  void MetalContext::SwapBuffers()
  {
    // Get next drawable
    CAMetalLayer* layer = static_cast<CAMetalLayer*>(mMetalLayer);
    id<CAMetalDrawable> drawable = [layer nextDrawable];
    if (!drawable)
      return;

    // Create command buffer
    MTL::CommandBuffer* cmdBuffer = mCommandQueue->commandBuffer();

    // Present the drawable
    [cmdBuffer presentDrawable:drawable];
    cmdBuffer->commit();
    cmdBuffer->release();
  }
}
