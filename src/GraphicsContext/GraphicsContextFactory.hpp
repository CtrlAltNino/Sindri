#pragma once

#include "IGraphicsContextFactory.hpp"

namespace Sindri
{
  class GraphicsContextFactory : public IGraphicsContextFactory
  {
  public:
    GraphicsContextFactory() = default;
    ~GraphicsContextFactory() override = default;

    /**
     * @brief Creates a graphics context and connects it to the SDL window
     *
     * @param window The SDL window to attach the graphics context to
     * @return Unique pointer to the creates graphics context
     */
    auto
    Create(SDL_Window* window) const
      -> std::unique_ptr<IGraphicsContext> override;
  };
} // namespace Sindri