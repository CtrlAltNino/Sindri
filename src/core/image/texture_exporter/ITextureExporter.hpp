#pragma once

namespace Sindri
{
  class ITextureExporter
  {
  public:
    virtual ~ITextureExporter() = default;

    virtual void
    Render() = 0;
  };
}