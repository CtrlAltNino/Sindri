#pragma once

#include "Gui/ImGui/IImGuiLayer.hpp"
#include "IImGuiLayerFactory.hpp"

namespace Sindri
{
  /**
   * @brief Factory class that creates ImGuiLayer instances based on the used
   * graphics api
   *
   */
  class ImGuiLayerFactory : public IImGuiLayerFactory
  {
  public:
    ~ImGuiLayerFactory() = default;

    /**
     * @brief Creates an ImGuiLayer instance
     *
     * @return Unique pointer to the created imgui layer
     */
    [[nodiscard]] auto
    Create() const -> std::unique_ptr<IImGuiLayer> override;
  };
} // namespace Sindri