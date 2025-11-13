#include "pch.hpp"

#include "Window.hpp"
#include <SDL3/SDL_video.h>

namespace Sindri
{
  SDL3Window::SDL3Window(
    std::shared_ptr<IGraphicsContextFactory> contextFactory,
    std::shared_ptr<IImGuiLayerFactory>      imguiLayerFactory)
    : mContextFactory(std::move(contextFactory))
    , mImguiLayerFactory(std::move(imguiLayerFactory))
  {
    // SDL Setup
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
      SDL_Quit();
      return;
    }

    mData.Title = "Sindri";
    mData.Height = 720;
    mData.Width = 1280;
    mData.ShouldClose = false;

    Uint32 windowFlags = 0;
    windowFlags |= SDL_WINDOW_HIDDEN;
    windowFlags |= SDL_WINDOW_MOUSE_CAPTURE;
    windowFlags |= SDL_WINDOW_RESIZABLE;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    windowFlags |= SDL_WINDOW_OPENGL;

    mWindow = SDL_CreateWindow(
      mData.Title.c_str(), mData.Width, mData.Height, windowFlags);

    if (mWindow == nullptr)
    {
      SDL_Quit();
      return;
    }

    const auto* mode =
      SDL_GetDesktopDisplayMode(SDL_GetDisplayForWindow(mWindow));

    SDL_SetWindowMinimumSize(mWindow, mData.Width, mData.Height);
    SDL_SetWindowPosition(mWindow,
                          (mode->w / 2) - (mData.Width / 2),
                          (mode->h / 2) - (mData.Height / 2));

    mContext = std::move(mContextFactory->Create(mWindow));

    if (mContext == nullptr)
    {
      SDL_DestroyWindow(mWindow);
      SDL_Quit();
    }

    mContext->Init();

    if (mData.VSync)
    {
      SDL_GL_SetSwapInterval(1);
    }
    else
    {
      SDL_GL_SetSwapInterval(0);
    }

    std::string deviceInfo;
    mImGuiLayer = std::move(mImguiLayerFactory->Create());

    if (mImGuiLayer == nullptr)
    {
      SDL_DestroyWindow(mWindow);
      SDL_Quit();
    }

    mImGuiLayer->OnAttach(mWindow);
  }

  SDL3Window::~SDL3Window()
  {
    mImGuiLayer->OnDetach();
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  void
  SDL3Window::ShowWindow()
  {
    SDL_ShowWindow(mWindow);
  }

  void
  SDL3Window::HideWindow()
  {
    SDL_HideWindow(mWindow);
  }

  void
  SDL3Window::NewFrame()
  {
    SDL_GetWindowSize(mWindow, &mData.Width, &mData.Height);
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      mImGuiLayer->HandleSDLEvent(&event);

      switch (event.type)
      {
        case SDL_EVENT_QUIT: mData.ShouldClose = true; break;
        default: break;
      }
    }
    mImGuiLayer->Begin();
  }

  void
  SDL3Window::EndFrame()
  {
    mImGuiLayer->End();
    mContext->SwapBuffers();
  }

  void
  SDL3Window::SetVSync(bool enabled)
  {
    if (enabled)
    {
      SDL_GL_SetSwapInterval(1);
    }
    else
    {
      SDL_GL_SetSwapInterval(0);
    }

    mData.VSync = enabled;
  }

  auto
  SDL3Window::IsVSync() -> bool
  {
    return mData.VSync;
  }

  auto
  SDL3Window::ShouldClose() -> bool
  {
    return mData.ShouldClose;
  }

  void
  SDL3Window::SetWindowTitle(std::string_view windowTitle)
  {
    SDL_SetWindowTitle(mWindow, windowTitle.data());
  }
}