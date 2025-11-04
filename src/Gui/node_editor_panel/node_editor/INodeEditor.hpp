#pragma once

#include <ImNodeFlow.h>
#include <imgui.h>

namespace Sindri
{
  class INodeEditor
  {
  public:
    virtual ~INodeEditor() = default;

    virtual void
    SetSize(ImVec2 size) = 0;

    virtual void
    Draw() = 0;

    virtual auto
    GetRootNode() -> ImFlow::ImNodeFlow* = 0;

    template<typename T, typename... Args>
      requires std::derived_from<T, ImFlow::BaseNode>
    auto
    AddNode(const ImVec2& pos, Args&&... args) -> std::shared_ptr<T>
    {
      return GetRootNode()->addNode<T>(pos, std::forward<Args>(args)...);
    }
  };
}