#include "pch.hpp"

#include "Sindri.hpp"
#include "SindriInjector.hpp"

auto
main() -> int
{
  auto sindriInjector = Sindri::SindriInjector::CreateInjector();
  auto sindriApp = sindriInjector.create<std::shared_ptr<Sindri::Sindri>>();

  sindriApp->Run();

  return 0;
}