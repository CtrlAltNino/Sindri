#pragma once

#include "GraphicsContext/IGraphicsContextFactory.hpp"
// #include "Editor/Stats/IEditorStats.hpp"
// #include "Input/IInputManager.hpp"
// #include "Logging/ISindriLogger.hpp"
#include "Gui/ImGui/IImGuiLayerFactory.hpp"
#include "Window/IWindow.hpp"

namespace Sindri
{
  class SDL3Window : public IWindow
  {
    struct WindowData
    {
      std::string Title;
      int         Width = 0;
      int         Height = 0;
      bool        VSync = true;
      bool        ShouldClose = false;
      glm::vec2   SavedMousePos = { -1, -1 };
    };

  private:
    SDL_Window*                              mWindow;
    std::unique_ptr<IGraphicsContext>        mContext;
    std::unique_ptr<IImGuiLayer>             mImGuiLayer;
    std::shared_ptr<IGraphicsContextFactory> mContextFactory;
    std::shared_ptr<IImGuiLayerFactory>      mImguiLayerFactory;

    WindowData mData;

  public:
    explicit SDL3Window(std::shared_ptr<IGraphicsContextFactory> contextFactory,
                        std::shared_ptr<IImGuiLayerFactory> imguiLayerFactory);
    ~SDL3Window() override;

    /**
     * @brief Running logic for the beginning of a frame
     *
     */
    void
    NewFrame() override;

    /**
     * @brief Running logic for the end of a frame
     *
     */
    void
    EndFrame() override;

    /**
     * @brief Gets the width of the window
     *
     * @return Width in pixels
     */
    [[nodiscard]] auto
    GetWidth() const -> uint32_t override
    {
      return mData.Width;
    }

    /**
     * @brief Gets the height of the window
     *
     * @return Height in pixels
     */
    [[nodiscard]] auto
    GetHeight() const -> uint32_t override
    {
      return mData.Height;
    }

    /**
     * @brief Shows the window
     *
     */
    void
    ShowWindow() override;

    /**
     * @brief Hides the window
     *
     */
    void
    HideWindow() override;

    /**
     * @brief Enables/Disables VSync
     *
     * @param enabled Desired VSync state
     */
    void
    SetVSync(bool enabled) override;

    /**
     * @brief Checks if VSync is enabled window based
     *
     * @return true Enable VSync
     * @return false Disable VSync
     */
    auto
    IsVSync() -> bool override;

    /**
     * @brief Checks the close signal of the window (E.g. pressing the close
     * button in the window title bar)
     *
     * @return true Window should close
     * @return false Window does not have a closing signal
     */
    auto
    ShouldClose() -> bool override;

    /**
     * @brief Sets the title of the window
     *
     * @param windowTitle Window title
     */
    void
    SetWindowTitle(std::string_view windowTitle) override;

    /**
     * @brief Gets the underlying SDL window pointer
     *
     * @return The raw SDL window pointer
     */
    [[nodiscard]] auto
    GetNativeWindow() const -> SDL_Window* override
    {
      return mWindow;
    }
  };
}