#pragma once

#include <SDL3/SDL.h>

namespace Sindri
{
  struct WindowProps
  {
    std::string Title = "Sindri";
    int         Width = 0;
    int         Height = 0;
    // GraphicsApi Api = GraphicsApi::OpenGL;
    // bool Resizable = false;
  };

  /**
   * @brief Class for abstracting window management
   *
   */
  class IWindow
  {
  public:
    virtual ~IWindow() = default;

    /**
     * @brief Running logic for the beginning of a frame
     *
     */
    virtual void
    NewFrame() = 0;

    /**
     * @brief Running logic for the end of a frame
     *
     */
    virtual void
    EndFrame() = 0;

    /**
     * @brief Gets the width of the window
     *
     * @return Width in pixels
     */
    [[nodiscard]] virtual auto
    GetWidth() const -> uint32_t = 0;

    /**
     * @brief Gets the height of the window
     *
     * @return Height in pixels
     */
    [[nodiscard]] virtual auto
    GetHeight() const -> uint32_t = 0;

    /**
     * @brief Enables/Disables VSync
     *
     * @param enabled Desired VSync state
     */
    virtual void
    SetVSync(bool enabled) = 0;

    /**
     * @brief Checks if VSync is enabled window based
     *
     * @return true Enable VSync
     * @return false Disable VSync
     */
    virtual auto
    IsVSync() -> bool = 0;

    /**
     * @brief Gets the underlying SDL window pointer
     *
     * @return The raw SDL window pointer
     */
    [[nodiscard]] virtual auto
    GetNativeWindow() const -> SDL_Window* = 0;

    /**
     * @brief Shows the window
     *
     */
    virtual void
    ShowWindow() = 0;

    /**
     * @brief Hides the window
     *
     */
    virtual void
    HideWindow() = 0;

    /**
     * @brief Checks the close signal of the window (E.g. pressing the close
     * button in the window title bar)
     *
     * @return true Window should close
     * @return false Window does not have a closing signal
     */
    virtual auto
    ShouldClose() -> bool = 0;

    /**
     * @brief Sets the title of the window
     *
     * @param windowTitle Window title
     */
    virtual void
    SetWindowTitle(std::string_view windowTitle) = 0;
  };
}