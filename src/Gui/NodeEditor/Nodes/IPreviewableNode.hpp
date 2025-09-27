#pragma once

#include "NodeTypes.hpp"

namespace Sindri
{
  class IPreviewableNode
  {
  private:
    // Texture ID
    // Size
    glm::ivec2 mResolution;
    // CPU sided texture buffer
    std::vector<float> mBuffer;
    bool               mIsUploaded = false;
    bool               mIsInvalid = true;

  public:
    IPreviewableNode()
    {
      //
    }

    ~IPreviewableNode()
    {
      // Free gpu texture
    }

    void
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
    FillWith(std::function<float(glm::vec2)> evaluationFunction)
    {
      int index = 0;
      for (int yCoord = 0; yCoord < mResolution.y; yCoord++)
      {
        for (int xCoord = 0; xCoord < mResolution.x; xCoord++)
        {
          mBuffer[index++] = evaluationFunction({ xCoord, yCoord });
        }
      }

      mIsInvalid = false;
      mIsUploaded = false;
    }

    void
    Upload()
    {
      mIsUploaded = true;
    }
  };
}