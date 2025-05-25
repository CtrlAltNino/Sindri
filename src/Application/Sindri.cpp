#include "pch.hpp"

#include "Sindri.hpp"
#include <chrono>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

namespace Sindri
{
  Sindri::Sindri(std::shared_ptr<ISindriGui>         gui,
                 std::shared_ptr<IWindow>            window,
                 std::shared_ptr<ITexturePreview>    preview,
                 std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture)
    : mGui(std::move(gui))
    , mWindow(std::move(window))
    , mPreview(std::move(preview))
    , mGpuPreviewTexture(std::move(gpuPreviewTexture))
  {
  }

  void
  Sindri::Run()
  {
    mWindow->ShowWindow();

    mPreview->Init();

    MainLoop();
  }

  void
  Sindri::MainLoop()
  {
    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    while (!mWindow->ShouldClose())
    {
      auto  now = clock::now();
      float deltaTime = std::chrono::duration<float>(now - lastTime).count();
      lastTime = now;

      mGui->Render(deltaTime);

      if (mGpuPreviewTexture->GetWaitingForUpload())
      {
        mGpuPreviewTexture->Upload();
      }

      // SDL_Delay(1); // prevent CPU spinlock
    }
  }
}