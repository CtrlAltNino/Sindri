#include "pch.hpp"

#include "Sindri.hpp"
#include <chrono>
#include <glm/gtc/type_ptr.hpp>

namespace Sindri
{
  Sindri::Sindri(std::shared_ptr<ISindriGui> gui,
                 std::shared_ptr<IWindow>    window)
    : mGui(std::move(gui))
    , mWindow(std::move(window))
  {
  }

  void
  Sindri::Run()
  {
    mWindow->ShowWindow();

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

      // SDL_Delay(1); // prevent CPU spinlock
    }
  }
}