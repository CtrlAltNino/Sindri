#pragma once

#include <glad/glad.h>

namespace Sindri
{
  class ITextureBuffer
  {
  public:
    virtual ~ITextureBuffer() = default;

    virtual void
    Reserve(size_t width) = 0;

    virtual void
    Reserve(size_t width, size_t height) = 0;

    virtual void
    Reserve(size_t width, size_t height, size_t depth) = 0;

    virtual auto
    GetData() -> std::vector<float>& = 0;

    /*void
    Upload();

    [[nodiscard]]
    auto
    GetTextureId() const -> uintptr_t
    {
      return mTextureId;
    }

    [[nodiscard]]
    auto
    GetIsUploaded() const -> bool
    {
      return mIsUploaded;
    }

    [[nodiscard]] auto
    GetInterpolatePreview() const -> bool;

    void
    SetInterpolatePreview(bool interpolate);

    [[nodiscard]] auto
    GetWaitingForUpload() const -> bool;

    void
    SetWaitingForUpload(bool waitingForUpload);*/
  };
}