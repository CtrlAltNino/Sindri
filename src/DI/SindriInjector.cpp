#include "pch.hpp"

#include "DI/SindriInjector.hpp"

namespace Sindri
{
  auto
  SindriInjector::CreateInjector()
    -> boost::di::injector<std::shared_ptr<Sindri>>
  {
    return boost::di::make_injector<boost::di::extension::shared_config>(
      boost::di::bind<ICameraFactory>.to<CameraFactory>().in(
        boost::di::extension::shared));
  }
}