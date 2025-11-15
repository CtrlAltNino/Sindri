#include "pch.hpp"

#include "GraphicsContextFactory.hpp"

#if defined(__APPLE__)
  #include "MetalContext.hpp"
#endif

#if defined(_WIN32) || (__linux__)
  #include "OpenGLContext.hpp"
#endif

namespace Sindri
{
  auto
  GraphicsContextFactory::Create(SDL_Window* window) const
    -> std::unique_ptr<IGraphicsContext>
  {
#if defined(__APPLE__)
    return std::make_unique<MetalContext>(window);
#elif defined(_WIN32) || defined(__linux__)
    return std::make_unique<OpenGLContext>(window);
#endif
  }
} // namespace Sindri