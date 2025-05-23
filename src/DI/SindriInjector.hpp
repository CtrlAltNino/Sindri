#pragma once

#include "Application/Sindri.hpp"

#include <boost/di.hpp>
#include <boost/di/extension/injections/lazy.hpp>
#include <boost/di/extension/scopes/shared.hpp>

namespace Sindri
{
  class SindriInjector
  {
  public:
    static auto
    CreateInjector() -> boost::di::injector<std::shared_ptr<Sindri>>;
  };
}