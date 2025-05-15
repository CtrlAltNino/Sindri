#include "StackEntry.hpp"
#include "pch.hpp"

#include "CompositionStack.hpp"

namespace Sindri
{
  CompositionStack::CompositionStack() {}

  void
  CompositionStack::Add(std::filesystem::path luaScriptPath)
  {
    mStack.push_back(StackEntry(luaScriptPath));
  }

  void
  CompositionStack::Remove(uint32_t index)
  {
    // std::erase(mStack, index);
  }

  auto
  CompositionStack::Evaluate(TextureSettings settings, glm::ivec3 coordinate)
    -> float
  {
    float value = 0;

    for (auto& stackEntry : mStack)
    {
      float computed = stackEntry.Evaluate(settings, coordinate);

      switch (stackEntry.GetComposeType())
      {
        using enum ComposeType;
        case Add: value += computed; break;
        case Multiply: value *= computed; break;
      }
    }

    return value;
  }

  auto
  CompositionStack::GetEntries() -> std::vector<StackEntry>&
  {
    return mStack;
  }
}