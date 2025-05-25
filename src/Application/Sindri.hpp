#pragma once

#include "IGpuPreviewTexture.hpp"
#include "ISindriGui.hpp"
#include "ITextureExporter.hpp"
#include "ITexturePreview.hpp"
#include "IWindow.hpp"
#include "TexturePipelineExecutor/ITexturePipelineExecutor.hpp"
#include <SDL3/SDL.h>

namespace Sindri
{
  class Sindri
  {
  private:
    std::shared_ptr<ISindriGui> mGui = nullptr;

    std::shared_ptr<IWindow> mWindow = nullptr;

    std::shared_ptr<ITextureExporter> mExporter = nullptr;

    std::shared_ptr<ITexturePreview> mPreview = nullptr;

    std::shared_ptr<ITexturePipelineExecutor> mPipelineExecutor;

    std::shared_ptr<IGpuPreviewTexture> mGpuPreviewTexture;

    void
    MainLoop();

  public:
    Sindri(std::shared_ptr<ISindriGui>         gui,
           std::shared_ptr<IWindow>            window,
           std::shared_ptr<ITexturePreview>    preview,
           std::shared_ptr<IGpuPreviewTexture> gpuPreviewTexture);
    ~Sindri() = default;

    Sindri(const Sindri&) = delete;
    auto
    operator=(const Sindri&) -> Sindri& = delete;

    void
    Run();
  };
}