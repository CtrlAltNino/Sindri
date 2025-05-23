#include "pch.hpp"

#include "TextureBuffer.hpp"

namespace Sindri
{
  auto
  TextureBuffer::GetData() -> std::vector<float>&
  {
    return mData;
  }
}