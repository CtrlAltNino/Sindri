#pragma once

#include "Gui/ImGui/IImGuiLayer.hpp"

namespace Sindri
{
  /**
   * @brief Factory class that creates ImGuiLayer instances based on the used
   * graphics api
   *
   */
  class IImGuiLayerFactory
  {
  public:
    virtual ~IImGuiLayerFactory() = default;

    /**
     * @brief Creates an ImGuiLayer instance
     *
     * @return Unique pointer to the created imgui layer
     */
    [[nodiscard]] virtual auto
    Create() const -> std::unique_ptr<IImGuiLayer> = 0;
  };
} // namespace Sindri