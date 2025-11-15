#include "pch.hpp"

#include "ImGuiLayerFactory.hpp"

#if defined(__APPLE__)
#include "MetalImGuiLayer.hpp"
#endif

#if defined(_WIN32) || (__linux__)
#include "OpenGLImGuiLayer.hpp"
#endif

namespace Sindri
{
  auto
  ImGuiLayerFactory::Create() const -> std::unique_ptr<IImGuiLayer>
  {
#if defined(__APPLE__)
    return std::make_unique<MetalImGuiLayer>();
#elif defined(_WIN32) || defined(__linux__)
    return std::make_unique<OpenGLImGuiLayer>();
#endif
  }
} // namespace Sindri