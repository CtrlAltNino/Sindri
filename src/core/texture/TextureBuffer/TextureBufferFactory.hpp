#pragma once

#include "ITextureBufferFactory.hpp"

namespace Sindri
{
  class TextureBufferFactory : public ITextureBufferFactory
  {
  public:
    ~TextureBufferFactory() override = default;

    auto
    Create() -> std::shared_ptr<ITextureBuffer> override;
  };
}