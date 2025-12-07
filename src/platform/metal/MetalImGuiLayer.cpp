#include "pch.hpp"

#define IMGUI_IMPL_METAL_CPP

#include "MetalImGuiLayer.hpp"
#include <MetalContext.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_metal.h>
#include <imgui_impl_metal.h>
#include <imgui_impl_sdl3.h>
#include <imgui_internal.h>
#include <memory>

namespace Sindri
{
  MetalImGuiLayer::~MetalImGuiLayer()
  {
    if ((mWindow != nullptr) && (ImGui::GetCurrentContext() != nullptr))
    {
      ImGui_ImplMetal_Shutdown();
      ImGui_ImplSDL3_Shutdown();
      ImGui::DestroyContext();
    }
  }

  void
  MetalImGuiLayer::OnAttach(SDL_Window*                       window,
                            std::shared_ptr<IGraphicsContext> graphicsContext)
  {
    mWindow = window;
    mGraphicsContext = graphicsContext;
    auto metalContext =
      std::dynamic_pointer_cast<MetalContext>(mGraphicsContext);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
    // Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    io.ConfigWindowsResizeFromEdges = true;
    io.FontDefault =
      io.Fonts->AddFontFromFileTTF("fonts/FiraCode-Regular.ttf", 16.0F);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if ((io.ConfigFlags) != 0)
    {
      style.WindowRounding = 0.0F;
      style.Colors[ImGuiCol_WindowBg].w = 1.0F;
    }

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForMetal(mWindow);
    ImGui_ImplMetal_Init(metalContext->GetDevice());
  }

  void
  MetalImGuiLayer::OnDetach()
  {
    ImGui_ImplMetal_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }

  void
  MetalImGuiLayer::Begin()
  {
    // ImGui_ImplMetal_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
  }

  void
  MetalImGuiLayer::End()
  {
    auto metalContext =
      std::dynamic_pointer_cast<MetalContext>(mGraphicsContext);

    ImGui::Render();
    ImDrawData* drawData = ImGui::GetDrawData();

    // Acquire drawable
    CA::MetalDrawable* drawable = metalContext->GetMetalLayer()->nextDrawable();
    if (drawable == nullptr)
    {
      return;
    }

    // Begin Metal commands
    MTL::CommandBuffer* cmd = metalContext->BeginFrame();

    // Create RenderPassDescriptor for ImGui
    MTL::RenderPassDescriptor* rpDesc =
      metalContext->CreateImGuiRenderPass(drawable);

    // Tell ImGui about it
    ImGui_ImplMetal_NewFrame(rpDesc);

    // Create encoder
    MTL::RenderCommandEncoder* encoder = cmd->renderCommandEncoder(rpDesc);

    // ImGui draws here
    ImGui_ImplMetal_RenderDrawData(drawData, cmd, encoder);

    encoder->endEncoding();
    encoder->release();
    rpDesc->release();

    // Present framebuffer
    cmd->presentDrawable(drawable);

    // Submit GPU work
    metalContext->EndFrame(cmd);
  }

  void
  MetalImGuiLayer::HandleSDLEvent(SDL_Event* event)
  {
    ImGui_ImplSDL3_ProcessEvent(event);
  }
}