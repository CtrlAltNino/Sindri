#include "pch.hpp"

#include "TextureBuffer.hpp"
#include "TextureBufferFactory.hpp"

namespace Sindri
{
  auto
  TextureBufferFactory::Create() -> std::shared_ptr<ITextureBuffer>
  {
    return std::make_shared<TextureBuffer>();
  }
}