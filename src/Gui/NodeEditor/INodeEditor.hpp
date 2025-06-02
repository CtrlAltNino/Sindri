#pragma once

namespace Sindri
{
  class INodeEditor
  {
  public:
    virtual ~INodeEditor() = default;

    virtual void
    Render() = 0;
  };
}