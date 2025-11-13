#include "pch.hpp"

#include "ImGuiLayerFactory.hpp"
#include "OpenGLImGuiLayer.hpp"

namespace Sindri
{
  auto
  ImGuiLayerFactory::Create() const -> std::unique_ptr<IImGuiLayer>
  {
    return std::make_unique<OpenGLImGuiLayer>();
  }
} // namespace Sindri