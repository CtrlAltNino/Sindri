#pragma once

#include "ISindriGui.hpp"
#include "IWindow.hpp"
#include <SDL3/SDL.h>

namespace Sindri
{
  /**
   * @brief Main class for the Sindri application.
   *
   */
  class Sindri
  {
  private:
    std::shared_ptr<ISindriGui> mGui = nullptr;

    std::shared_ptr<IWindow> mWindow = nullptr;

    /**
     * @brief Function containing the main application loop.
     *
     */
    void
    MainLoop();

  public:
    Sindri(std::shared_ptr<ISindriGui> gui, std::shared_ptr<IWindow> window);
    ~Sindri() = default;

    Sindri(const Sindri&) = delete;
    auto
    operator=(const Sindri&) -> Sindri& = delete;

    /**
     * @brief Runs the application.
     *
     */
    void
    Run();
  };
}