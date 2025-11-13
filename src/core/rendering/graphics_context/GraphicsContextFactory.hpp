#pragma once

#include "IGraphicsContextFactory.hpp"

namespace Sindri
{
  /// @copydoc IGraphicsContextFactory
  class GraphicsContextFactory : public IGraphicsContextFactory
  {
  public:
    GraphicsContextFactory() = default;
    ~GraphicsContextFactory() override = default;

    /// @copydoc IGraphicsContextFactory::Create
    auto
    Create(SDL_Window* window) const
      -> std::unique_ptr<IGraphicsContext> override;
  };
} // namespace Sindri