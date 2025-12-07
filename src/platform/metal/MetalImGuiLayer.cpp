#include "pch.hpp"

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
    auto metalContext =
      std::dynamic_pointer_cast<MetalContext>(graphicsContext);
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
    ImGui_ImplMetal_Init("#version 410");
  }

  void
  MetalImGuiLayer::OnDetach()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
  }

  void
  MetalImGuiLayer::Begin()
  {
    ImGui_ImplMetal_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
  }

  void
  MetalImGuiLayer::End()
  {
    const ImGuiIO* io = &ImGui::GetIO();
    ImGui::Render();
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData());
    /*if ((io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0)
    {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }*/
  }

  void
  MetalImGuiLayer::HandleSDLEvent(SDL_Event* event)
  {
    ImGui_ImplSDL3_ProcessEvent(event);
  }
}