#include "pch.hpp"

#include "GpuPreviewTextureFactory.hpp"
#include "GraphicsContextFactory.hpp"
#include "IGraphicsContextFactory.hpp"
#include "IImGuiLayerFactory.hpp"
#include "INoiseLayerFactory.hpp"
#include "ITextureBufferFactory.hpp"
#include "ImGuiLayerFactory.hpp"
#include "NodeEditor.hpp"
#include "NodeEditorPanel.hpp"
#include "NoiseLayerFactory.hpp"
#include "SindriGui.hpp"
#include "SindriInjector.hpp"
#include "TextureBuffer.hpp"
#include "TextureBufferFactory.hpp"
#include "VariableRegistry.hpp"
#include "VariablesPanel.hpp"
#include "Window.hpp"
#include "WorkflowSettingsPanel.hpp"
#include <boost/di.hpp>

namespace Sindri
{
  auto
  SindriInjector::CreateInjector()
    -> boost::di::injector<std::shared_ptr<Sindri>>
  {
    return boost::di::make_injector<boost::di::extension::shared_config>(
      boost::di::bind<ITextureBuffer>.to<TextureBuffer>().in(
        boost::di::extension::shared),
      boost::di::bind<IVariableRegistry>.to<VariableRegistry>().in(
        boost::di::extension::shared),
      boost::di::bind<ITextureBufferFactory>.to<TextureBufferFactory>().in(
        boost::di::extension::shared),
      boost::di::bind<IGpuPreviewTextureFactory>.to<GpuPreviewTextureFactory>().in(
        boost::di::extension::shared),
      boost::di::bind<INodeEditor>.to<NodeEditor>().in(
        boost::di::extension::shared),
      boost::di::bind<INodeEditorPanel>.to<NodeEditorPanel>().in(
        boost::di::extension::shared),
      boost::di::bind<IVariablesPanel>.to<VariablesPanel>().in(
        boost::di::extension::shared),
      boost::di::bind<IWorkflowSettings>.to<WorkflowSettings>().in(
        boost::di::extension::shared),
      boost::di::bind<IWorkflowSettingsPanel>.to<WorkflowSettingsPanel>().in(
        boost::di::extension::shared),
      boost::di::bind<IWindow>.to<SDL3Window>().in(
        boost::di::extension::shared),
      boost::di::bind<IGraphicsContextFactory>.to<GraphicsContextFactory>().in(
        boost::di::extension::shared),
      boost::di::bind<IImGuiLayerFactory>.to<ImGuiLayerFactory>().in(
        boost::di::extension::shared),
      boost::di::bind<INoiseLayerFactory>.to<NoiseLayerFactory>().in(
        boost::di::extension::shared),
      boost::di::bind<ISindriGui>.to<SindriGui>().in(
        boost::di::extension::shared));
  }
}