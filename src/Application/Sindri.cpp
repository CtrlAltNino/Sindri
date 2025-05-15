#include "pch.hpp"

#include "Sindri.hpp"
#include <chrono>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <iostream>

namespace Sindri
{
  SindriApp::SindriApp()
  {
    if (!Init())
    {
      std::cerr << "[Error] Failed to initialize SindriApp.\n";
    }
  }

  SindriApp::~SindriApp()
  {
    Shutdown();
  }

  auto
  SindriApp::Init() -> bool
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
      std::cerr << "[SDL] Initialization Error: " << SDL_GetError() << "\n";
      return false;
    }

    m_Window = SDL_CreateWindow(
      m_Title.c_str(), m_Width, m_Height, SDL_WINDOW_RESIZABLE);
    if (!m_Window)
    {
      std::cerr << "[SDL] Failed to create window: " << SDL_GetError() << "\n";
      return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    // SDL3: Third argument is now a const char* driver name (or nullptr)
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if (!m_Renderer)
    {
      std::cerr << "[SDL] Failed to create renderer: " << SDL_GetError()
                << "\n";
      return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer))
    {
      std::cerr << "[ImGui] SDL3 init failed\n";
      return false;
    }

    if (!ImGui_ImplSDLRenderer3_Init(m_Renderer))
    {
      std::cerr << "[ImGui] SDL_Renderer3 init failed\n";
      return false;
    }

    m_Running = true;
    return true;
  }

  void
  SindriApp::Shutdown()
  {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    if (m_Renderer)
    {
      SDL_DestroyRenderer(m_Renderer);
      m_Renderer = nullptr;
    }

    if (m_Window)
    {
      SDL_DestroyWindow(m_Window);
      m_Window = nullptr;
    }

    SDL_Quit();
  }

  void
  SindriApp::Run()
  {
    if (!m_Running)
    {
      std::cerr << "[SindriApp] Cannot run main loop; init failed.\n";
      return;
    }

    MainLoop();
  }

  void
  SindriApp::MainLoop()
  {
    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    while (m_Running)
    {
      auto  now = clock::now();
      float deltaTime = std::chrono::duration<float>(now - lastTime).count();
      lastTime = now;
      mFps = 1.0f / deltaTime;
      mMsPerFrame = deltaTime * 1000.0f;

      HandleEvents();

      ImGui_ImplSDLRenderer3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      // Demo window for testing
      // ImGui::ShowDemoWindow();
      MainWindow();

      Render();

      SDL_Delay(1); // prevent CPU spinlock
    }
  }

  void
  SindriApp::HandleEvents()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL3_ProcessEvent(&event);
      switch (event.type)
      {
        case SDL_EVENT_QUIT: m_Running = false; break;
        default: break;
      }
    }
  }

  void
  SindriApp::Render()
  {
    ImGui::Render();

    SDL_SetRenderDrawColor(m_Renderer, 0x1e, 0x1e, 0x1e, 0xff);
    SDL_RenderClear(m_Renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Renderer);

    // Your rendering code here

    SDL_RenderPresent(m_Renderer);
  }

  void
  SindriApp::MainWindow()
  {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(m_Window, &windowWidth, &windowHeight);
    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));

    // Create a full-screen ImGui window
    ImGui::Begin("MainWindow", nullptr, windowFlags);
    ImGui::Text("Welcome to SindriApp!");
    ImGui::Separator();
    ImGui::Text("This window fills the whole SDL window.");

    ImGui::Text("FPS: %.1f", mFps);
    ImGui::Text("Frame Time: %.2f ms", mMsPerFrame);
    // You can add buttons, sliders, etc. here
    ImGui::End();
  }
}