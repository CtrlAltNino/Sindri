#pragma once

#include "ITextureBuffer.hpp"
namespace Sindri
{
  class ITextureBufferFactory
  {
  public:
    virtual ~ITextureBufferFactory() = default;

    virtual auto
    Create() -> std::shared_ptr<ITextureBuffer> = 0;
  };
}