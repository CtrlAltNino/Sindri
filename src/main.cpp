#include "DI/SindriInjector.hpp"
#include "pch.hpp"

#include "Application/Sindri.hpp"

auto
main() -> int
{
  auto sindriInjector = Sindri::SindriInjector::CreateInjector();
  auto sindriApp = sindriInjector.create<std::shared_ptr<Sindri::Sindri>>();

  sindriApp->Run();

  return 0;
}