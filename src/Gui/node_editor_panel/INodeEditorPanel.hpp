#pragma once

namespace Sindri
{
  class INodeEditorPanel
  {
  public:
    virtual ~INodeEditorPanel() = default;

    virtual void
    Render() = 0;
  };
}