#include "pch.hpp"

#include "SindriGui.hpp"
#include <imgui.h>

namespace Sindri
{
  SindriGui::SindriGui(
    std::shared_ptr<IWindow>                  window,
    std::shared_ptr<IWorkflowSettingsPanel>   workflowSettingsPanel,
    std::shared_ptr<ITexturePipeline>         texturePipeline,
    std::shared_ptr<ITextureExporter>         exporter,
    std::shared_ptr<ITextureBuffer>           textureBuffer,
    std::shared_ptr<ITexturePreview>          preview,
    std::shared_ptr<IGpuPreviewTexture>       gpuPreviewTexture,
    std::shared_ptr<ITexturePipelineExecutor> texturePipelineExecutor,
    std::shared_ptr<INodeEditorPanel>         nodeEditor,
    std::shared_ptr<IVariablesPanel>          variablesGui)
    : mWindow(std::move(window))
    , mWorkflowSettingsPanel(std::move(workflowSettingsPanel))
    , mTexturePipeline(std::move(texturePipeline))
    , mExporter(std::move(exporter))
    , mTextureBuffer(std::move(textureBuffer))
    , mPreview(std::move(preview))
    , mGpuPreviewTexture(std::move(gpuPreviewTexture))
    , mExecutor(std::move(texturePipelineExecutor))
    , mNodeEditor(std::move(nodeEditor))
    , mVariablesGui(std::move(variablesGui))
  {
    SetupImGuiStyles();
  }

  void
  SindriGui::RenderImGui(float deltaTime)
  {
    RenderVariablesWindow(deltaTime,
                          ImVec2(0, 0),
                          ImVec2((float)mWindow->GetWidth() * (1.0F / 3.0F),
                                 (float)mWindow->GetHeight() / 2.0F));

    RenderWorkflowSettingsWindow(
      deltaTime,
      ImVec2(0, (float)mWindow->GetHeight() / 2.0F),
      ImVec2((float)mWindow->GetWidth() * (1.0F / 3.0F),
             (float)mWindow->GetHeight() / 2.0F));

    RenderNodeEditorWindow(
      deltaTime,
      ImVec2((float)mWindow->GetWidth() * (1.0F / 3.0F), 0),
      ImVec2((float)mWindow->GetWidth() * (2.0F / 3.0F),
             (float)mWindow->GetHeight()));
  }

  void
  SindriGui::RenderVariablesWindow(float  deltaTime,
                                   ImVec2 position,
                                   ImVec2 size)
  {
    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);

    ImGui::Begin("PreviewWindow", nullptr, windowFlags);
    ImGui::SeparatorText("Variables");

    mVariablesGui->Render();

    // You can add buttons, sliders, etc. here
    ImGui::End();
  }

  void
  SindriGui::RenderWorkflowSettingsWindow(float  deltaTime,
                                          ImVec2 position,
                                          ImVec2 size)
  {
    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);

    // Create a full-screen ImGui window
    ImGui::Begin("SettingsWindow", nullptr, windowFlags);

    mWorkflowSettingsPanel->Render();

    // You can add buttons, sliders, etc. here
    ImGui::End();
  }

  void
  SindriGui::RenderNodeEditorWindow(float  deltaTime,
                                    ImVec2 position,
                                    ImVec2 size)
  {
    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);

    // Create a full-screen ImGui window
    ImGui::Begin("NodeEditorWindow", nullptr, windowFlags);
    ImGui::SeparatorText("Node Editor");

    mNodeEditor->Render();

    // You can add buttons, sliders, etc. here
    ImGui::End();
  }

  void
  SindriGui::Render(float deltaTime)
  {
    mWindow->NewFrame();
    RenderImGui(deltaTime);
    mWindow->EndFrame();
  }

  void
  SindriGui::SetupImGuiStyles()
  {
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Polar Night
    colors[ImGuiCol_Text] = ImVec4(0.847F, 0.871F, 0.914F, 1.00F); // #D8DEE9
    colors[ImGuiCol_TextDisabled] =
      ImVec4(0.533F, 0.573F, 0.678F, 1.00F); // #8892AD
    colors[ImGuiCol_WindowBg] =
      ImVec4(0.180F, 0.204F, 0.251F, 1.00F); // #2E3440
    colors[ImGuiCol_ChildBg] = ImVec4(0.180F, 0.204F, 0.251F, 1.00F);
    colors[ImGuiCol_PopupBg] = ImVec4(0.180F, 0.204F, 0.251F, 1.00F);
    colors[ImGuiCol_Border] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F); // #4C566A
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0F, 0.0F, 0.0F, 0.0F);

    // Frost
    colors[ImGuiCol_FrameBg] = ImVec4(0.231F, 0.259F, 0.322F, 1.00F); // #3B4252
    colors[ImGuiCol_FrameBgHovered] =
      ImVec4(0.369F, 0.506F, 0.675F, 1.00F); // #5E81AC
    colors[ImGuiCol_FrameBgActive] =
      ImVec4(0.506F, 0.631F, 0.757F, 1.00F); // #8191C1

    colors[ImGuiCol_TitleBg] = ImVec4(0.180F, 0.204F, 0.251F, 1.00F); // #2E3440
    colors[ImGuiCol_TitleBgActive] =
      ImVec4(0.231F, 0.259F, 0.322F, 1.00F); // #3B4252
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.180F, 0.204F, 0.251F, 0.78F);

    colors[ImGuiCol_MenuBarBg] = ImVec4(0.231F, 0.259F, 0.322F, 1.00F);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.180F, 0.204F, 0.251F, 1.00F);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F);
    colors[ImGuiCol_ScrollbarGrabHovered] =
      ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_ScrollbarGrabActive] =
      ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_CheckMark] =
      ImVec4(0.533F, 0.753F, 0.816F, 1.00F); // #88C0D0
    colors[ImGuiCol_SliderGrab] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_Button] = ImVec4(0.231F, 0.259F, 0.322F, 1.00F);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_Header] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_Separator] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_ResizeGrip] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);

    colors[ImGuiCol_Tab] = ImVec4(0.298F, 0.337F, 0.416F, 1.00F);
    colors[ImGuiCol_TabHovered] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_TabActive] = ImVec4(0.506F, 0.631F, 0.757F, 1.00F);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.231F, 0.259F, 0.322F, 1.00F);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);

    colors[ImGuiCol_PlotLines] =
      ImVec4(0.533F, 0.753F, 0.816F, 1.00F); // #88C0D0
    colors[ImGuiCol_PlotLinesHovered] =
      ImVec4(0.706F, 0.557F, 0.678F, 1.00F); // #B48EAD
    colors[ImGuiCol_PlotHistogram] =
      ImVec4(0.847F, 0.682F, 0.369F, 1.00F); // #EBCB8B
    colors[ImGuiCol_PlotHistogramHovered] =
      ImVec4(0.749F, 0.380F, 0.416F, 1.00F); // #BF616A

    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.369F, 0.506F, 0.675F, 1.00F);
    colors[ImGuiCol_NavWindowingHighlight] =
      ImVec4(0.506F, 0.631F, 0.757F, 1.00F);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.180F, 0.204F, 0.251F, 0.70F);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.180F, 0.204F, 0.251F, 0.78F);

    ImGuiStyle& style = ImGui::GetStyle();

    // These values are commonly adjusted for visual feel and alignment with the
    // Nord theme
    style.WindowRounding = 5.0F;
    style.FrameRounding = 4.0F;
    style.GrabRounding = 4.0F;
    style.ScrollbarRounding = 6.0F;
    style.TabRounding = 4.0F;
    style.PopupRounding = 4.0F;

    style.FramePadding = ImVec2(6.0F, 4.0F);
    style.ItemSpacing = ImVec2(8.0F, 6.0F);
    style.ItemInnerSpacing = ImVec2(6.0F, 4.0F);
    style.IndentSpacing = 20.0F;
    style.ScrollbarSize = 14.0F;
    style.GrabMinSize = 10.0F;

    style.WindowPadding = ImVec2(8.0F, 8.0F);
    style.WindowTitleAlign = ImVec2(0.5F, 0.5F); // Center title
  }
}