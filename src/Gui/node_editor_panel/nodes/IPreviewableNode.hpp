#pragma once

#include <utility>

#include "IGpuPreviewTexture.hpp"
#include "NodeTypes.hpp"

namespace Sindri
{
  class IPreviewableNode
  {
  private:
    // Texture ID
    // Size
    // glm::ivec3 mResolution;
    // CPU sided texture buffer
    // std::vector<float> mBuffer;

    // std::shared_ptr <

    // bool mIsUploaded = false;
    // bool   mIsInvalid = true;
    std::shared_ptr<IGpuPreviewTexture> mPreviewTexture;

  public:
    IPreviewableNode(std::shared_ptr<IGpuPreviewTexture> previewTexture)
      : mPreviewTexture(std::move(previewTexture))
    {
      //
    }

    ~IPreviewableNode()
    {
      // Free gpu texture
    }

    auto
    GetPreviewTexture() -> std::shared_ptr<IGpuPreviewTexture>
    {
      return mPreviewTexture;
    }

    /*void
    Invalidate()
    {
      // Set IsInvalid flag
      mIsInvalid = true;
    }

    [[nodiscard]] auto
    isUploaded() const -> bool
    {
      return mIsUploaded;
    }

    [[nodiscard]] auto
    IsInvalid() const -> bool
    {
      return mIsInvalid;
    }

    void
    Resize(glm::ivec2 newSize)
    {
      // Set size
      mResolution = newSize;
      mBuffer.clear();
      mBuffer.resize(newSize.y * newSize.x);
      // Invalidate
      Invalidate();
    }

    void
    FillWith(std::function<float(glm::vec3)> evaluationFunction)
    {
      int index = 0;
      */
    /*for (int zCoord = 0; zCoord < mResolution.z; zCoord++)
    {
      for (int yCoord = 0; yCoord < mResolution.y; yCoord++)
      {
        for (int xCoord = 0; xCoord < mResolution.x; xCoord++)
        {
          mBuffer[index++] = evaluationFunction({ xCoord, yCoord, zCoord });
        }
      }
    }*/

    /*mIsInvalid = false;
    mIsUploaded = false;
  }

  void
  Upload()
  {
    mIsUploaded = true;
  }*/
  };
}