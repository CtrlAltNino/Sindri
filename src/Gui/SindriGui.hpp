#pragma once

#include "Gui/ISindriGui.hpp"
namespace Sindri
{
  class SindriGui : public ISindriGui
  {
  private:
  std::shared_ptr < public : SindriGui() ~SindriGui() override = default;

    void
    Render() override;
  };
}