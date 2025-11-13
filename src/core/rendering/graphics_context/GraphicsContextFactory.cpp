#include "pch.hpp"

#include "GraphicsContextFactory.hpp"
#include "OpenGLContext.hpp"

namespace Sindri
{
  auto
  GraphicsContextFactory::Create(SDL_Window* window) const
    -> std::unique_ptr<IGraphicsContext>
  {
    return std::make_unique<OpenGLContext>(window);
  }
} // namespace Sindri