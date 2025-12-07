#include "pch.hpp"

#include "MetalContext.hpp"
#include <iostream>

namespace Sindri
{
  MetalContext::MetalContext(SDL_Window* windowHandle)
    : mWindowHandle(windowHandle)
  {
  }

  MetalContext::~MetalContext()
  {
    if (mCommandQueue != nullptr)
    {
      mCommandQueue->release();
    }

    if (mDevice != nullptr)
    {
      mDevice->release();
    }

    if (mMetalView != nullptr)
    {
      SDL_Metal_DestroyView(mMetalView);
    }
  }

  void
  MetalContext::Init()
  {
    //
    // 1) Create the SDL Metal View (NSView wrapper)
    //
    mMetalView = SDL_Metal_CreateView(mWindowHandle);
    if (mMetalView == nullptr)
    {
      std::cerr << "[MetalContext] Failed to create SDL_MetalView\n";
      return;
    }

    //
    // 2) Get the CAMetalLayer from SDL
    //
    mMetalLayer =
      reinterpret_cast<CA::MetalLayer*>(SDL_Metal_GetLayer(mMetalView));
    if (mMetalLayer == nullptr)
    {
      std::cerr << "[MetalContext] Failed to get CAMetalLayer from SDL\n";
      return;
    }

    //
    // 3) Create Metal device
    //
    mDevice = MTL::CreateSystemDefaultDevice();
    if (mDevice == nullptr)
    {
      std::cerr << "[MetalContext] Failed to create MTL::Device\n";
      return;
    }

    //
    // 4) Configure CAMetalLayer (metal-cpp style)
    //
    mMetalLayer->setDevice(mDevice);
    mMetalLayer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    mMetalLayer->setFramebufferOnly(true);

    //
    // 5) Create command queue
    //
    mCommandQueue = mDevice->newCommandQueue();
    if (mCommandQueue == nullptr)
    {
      std::cerr << "[MetalContext] Failed to create MTL::CommandQueue\n";
      return;
    }

    std::cout << "[MetalContext] Metal initialized successfully.\n";
  }

  void
  MetalContext::SwapBuffers()
  {
    if ((mMetalLayer == nullptr) || (mCommandQueue == nullptr))
    {
      return;
    }

    //
    // 1) Acquire next drawable
    //
    CA::MetalDrawable* drawable = mMetalLayer->nextDrawable();
    if (drawable == nullptr)
    {
      return;
    }

    //
    // 2) Create command buffer
    //
    MTL::CommandBuffer* cmdBuffer = mCommandQueue->commandBuffer();
    if (cmdBuffer == nullptr)
    {
      return;
    }

    //
    // 3) Present drawable
    //
    cmdBuffer->presentDrawable(drawable);

    //
    // 4) Commit buffer
    //
    cmdBuffer->commit();

    // Optional (only if you want strict CPU sync)
    // cmdBuffer->waitUntilCompleted();

    cmdBuffer->release();
  }

  MTL::CommandBuffer*
  MetalContext::BeginFrame()
  {
    return mCommandQueue->commandBuffer();
  }

  auto
  MetalContext::CreateImGuiRenderPass(CA::MetalDrawable* drawable)
    -> MTL::RenderPassDescriptor*
  {
    MTL::RenderPassDescriptor* rpDesc =
      MTL::RenderPassDescriptor::alloc()->init();

    auto colorAttachment = rpDesc->colorAttachments()->object(0);
    colorAttachment->setTexture(drawable->texture());
    colorAttachment->setLoadAction(MTL::LoadActionClear);
    colorAttachment->setClearColor(MTL::ClearColor(0.1, 0.1, 0.1, 1.0));
    colorAttachment->setStoreAction(MTL::StoreActionStore);

    return rpDesc; // caller will release later
  }

  void
  MetalContext::EndFrame(MTL::CommandBuffer* cmdBuffer)
  {
    cmdBuffer->commit();
    cmdBuffer->release();
  }

  void
  MetalContext::SetVsync(bool vsync)
  {
  }

}
