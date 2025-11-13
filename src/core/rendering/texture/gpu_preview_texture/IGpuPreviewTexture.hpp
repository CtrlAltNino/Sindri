#pragma once

#include "ITextureBuffer.hpp"
#include <cstdint>

namespace Sindri
{
  class IGpuPreviewTexture
  {
  public:
    virtual ~IGpuPreviewTexture() = default;

    virtual auto
    GetTextureBuffer() -> std::shared_ptr<ITextureBuffer> = 0;

    virtual void
    Upload() = 0;

    [[nodiscard]]
    virtual auto
    GetTextureId() const -> uintptr_t = 0;

    [[nodiscard]]
    virtual auto
    GetIsUploaded() const -> bool = 0;

    [[nodiscard]] virtual auto
    GetInterpolatePreview() const -> bool = 0;

    virtual void
    SetInterpolatePreview(bool interpolate) = 0;

    [[nodiscard]] virtual auto
    GetWaitingForUpload() const -> bool = 0;

    virtual void
    SetWaitingForUpload(bool waitingForUpload) = 0;
  };
}