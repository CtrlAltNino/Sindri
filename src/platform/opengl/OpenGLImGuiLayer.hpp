#pragma once

#include "IImGuiLayer.hpp"
#include <SDL3/SDL_video.h>

namespace Sindri
{
  class OpenGLImGuiLayer : public IImGuiLayer
  {
  private:
    SDL_Window* mWindow = nullptr;

  public:
    OpenGLImGuiLayer() = default;
    ~OpenGLImGuiLayer() override;

    /**
     * @brief Initializes the ImGui context for a given SDL window
     *
     * @param window
     */
    void
    OnAttach(SDL_Window*                       window,
             std::shared_ptr<IGraphicsContext> graphicsContext) override;

    /**
     * @brief Cleans up the imgui context
     *
     */
    void
    OnDetach() override;

    /**
     * @brief Start of a frame
     *
     */
    void
    Begin() override;

    /**
     * @brief End of a frame
     *
     */
    void
    End() override;

    /**
     * @brief Handles a SDL Event
     *
     * @param event
     */
    void
    HandleSDLEvent(SDL_Event* event) override;
  };
}