#pragma once

#include "StackEntry.hpp"
#include "TextureSettings/TextureSettings.hpp"

namespace Sindri
{
  class CompositionStack
  {
  private:
    std::vector<StackEntry> mStack;

  public:
    CompositionStack();

    void
    Add(std::filesystem::path luaScriptPath);

    void
    Remove(uint32_t index);

    auto
    GetEntries() -> std::vector<StackEntry>&;

    void
    RenderSettings();
  };
}