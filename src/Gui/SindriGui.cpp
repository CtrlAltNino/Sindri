#include "pch.hpp"

#include "SindriGui.hpp"
#include "TextureSettings/TextureSettings.hpp"
#include <imgui.h>

namespace Sindri
{
  SindriGui::SindriGui(
    std::shared_ptr<IWindow>                  window,
    std::shared_ptr<TextureSettings>          textureSettings,
    std::shared_ptr<ITexturePipeline>         texturePipeline,
    std::shared_ptr<ITextureExporter>         exporter,
    std::shared_ptr<ITextureBuffer>           textureBuffer,
    std::shared_ptr<ITexturePreview>          preview,
    std::shared_ptr<IGpuPreviewTexture>       gpuPreviewTexture,
    std::shared_ptr<ITexturePipelineExecutor> texturePipelineExecutor)
    : mWindow(std::move(window))
    , mTextureSettings(std::move(textureSettings))
    , mTexturePipeline(std::move(texturePipeline))
    , mExporter(std::move(exporter))
    , mTextureBuffer(std::move(textureBuffer))
    , mPreview(std::move(preview))
    , mGpuPreviewTexture(std::move(gpuPreviewTexture))
    , mExecutor(std::move(texturePipelineExecutor))
  {
    mTextureSettings->Seed = mRandomDevice();
    mScripts = GetLuaScripts();
  }

  void
  SindriGui::RenderImGui(float deltaTime)
  {
    mFps = 1.0F / deltaTime;
    mMsPerFrame = deltaTime * 1000.0F;

    // Set window flags to disable interactions and visuals
    ImGuiWindowFlags windowFlags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)mWindow->GetWidth() * (1.0F / 3.0F),
                                    (float)mWindow->GetHeight()));

    // Create a full-screen ImGui window
    ImGui::Begin("SettingsWindow", nullptr, windowFlags);
    ImGui::SeparatorText("General");

    ImGui::Text("FPS: %.1f", mFps);
    ImGui::Text("Frame Time: %.2f ms", mMsPerFrame);

    static bool vsync = mWindow->IsVSync();
    if (ImGui::Checkbox("VSync", &vsync))
    {
      // SDL_GL_SetSwapInterval(mVsync ? 1 : 0);
      mWindow->SetVSync(vsync);
    }

    ImGui::Spacing();
    ImGui::SeparatorText("Options");

    ImGui::InputScalar("Seed", ImGuiDataType_U32, &mTextureSettings->Seed);

    ImGui::SameLine();
    if (ImGui::Button("Randomize"))
    {
      mTextureSettings->Seed = mRandomDevice();
    }

    if (ImGui::RadioButton("Texture 1D",
                           mTextureSettings->Dimensions ==
                             TextureDimension::Texture1D))
    {
      mTextureSettings->Dimensions = TextureDimension::Texture1D;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Texture 2D",
                           mTextureSettings->Dimensions ==
                             TextureDimension::Texture2D))
    {
      mTextureSettings->Dimensions = TextureDimension::Texture2D;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Texture 3D",
                           mTextureSettings->Dimensions ==
                             TextureDimension::Texture3D))
    {
      mTextureSettings->Dimensions = TextureDimension::Texture3D;
    }

    // TODO: Variable channel amount

    switch (mTextureSettings->Dimensions)
    {
      using enum TextureDimension;
      case Texture1D:
        ImGui::InputInt("Resolution",
                        glm::value_ptr(mTextureSettings->Resolution));
        break;
      case Texture2D:
        ImGui::InputInt2("Resolution",
                         glm::value_ptr(mTextureSettings->Resolution));
        break;
      case Texture3D:
        ImGui::InputInt3("Resolution",
                         glm::value_ptr(mTextureSettings->Resolution));
        break;
    }

    ImGui::Spacing();
    ImGui::SeparatorText("Preview Settings");

    mPreview->RenderSettings();

    ImGui::Spacing();
    ImGui::SeparatorText("Lua Scripts");

    LuaScriptSelector();

    ImGui::Spacing();
    ImGui::SeparatorText("Noise Layers");

    // Composition
    if (mTexturePipeline->GetLayers().empty())
    {
      ImGui::Text("Your composition is empty, add layers above");
    }
    else
    {
      mTexturePipeline->RenderAllSettings();
    }

    if (mTexturePipeline->GetLayers().empty() || mExecutor->IsRunning())
    {
      ImGui::BeginDisabled();
    }

    ImGui::Spacing();
    ImGui::Separator();

    if (ImGui::Button("Generate"))
    {
      GenerateTexture();
    }

    if (mTexturePipeline->GetLayers().empty() || mExecutor->IsRunning())
    {
      ImGui::EndDisabled();
    }

    ImGui::SameLine();

    if (mTextureBuffer->GetData().empty() || mExecutor->IsRunning())
    {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button("Export"))
    {
      ImGui::OpenPopup("Export##ExportModal");
    }

    if (mTextureBuffer->GetData().empty() || mExecutor->IsRunning())
    {
      ImGui::EndDisabled();
    }

    if (mExecutor->IsRunning())
    {
      ImGui::SameLine();
      if (ImGui::Button("Cancel"))
      {
        mExecutor->CancelExecution();
      }
      ImGui::SameLine();
      ImGui::ProgressBar(mExecutor->GetProgress(),
                         ImVec2(ImGui::GetContentRegionAvail().x, 0.0F));
    }

    mExporter->Render();

    // You can add buttons, sliders, etc. here
    ImGui::End();

    // Set next window position and size to fill the screen
    ImGui::SetNextWindowPos(
      ImVec2((float)mWindow->GetWidth() * (1.0F / 3.0F), 0));
    ImGui::SetNextWindowSize(ImVec2((float)mWindow->GetWidth() * (2.0F / 3.0F),
                                    (float)mWindow->GetHeight()));

    ImGui::Begin("PreviewWindow", nullptr, windowFlags);
    ImGui::SeparatorText("Texture Preview");

    // Note: cast GLuint to void* to pass as ImTextureID
    if (mGpuPreviewTexture->GetIsUploaded())
    {
      ImVec2 position = ImGui::GetCursorPos();

      if (ImGui::GetContentRegionAvail().x <= ImGui::GetContentRegionAvail().y)
      {
        position.y += (ImGui::GetContentRegionAvail().y -
                       ImGui::GetContentRegionAvail().x) /
                      2.0F;
      }
      else if (ImGui::GetContentRegionAvail().y <
               ImGui::GetContentRegionAvail().x)
      {
        position.x += (ImGui::GetContentRegionAvail().x -
                       ImGui::GetContentRegionAvail().y) /
                      2.0F;
      }

      ImGui::SetCursorPos(position);

      glm::vec2 size = glm::vec2(ImGui::GetContentRegionAvail().x <=
                                     ImGui::GetContentRegionAvail().y
                                   ? ImGui::GetContentRegionAvail().x
                                   : ImGui::GetContentRegionAvail().y);

      mPreview->Render(size, deltaTime);
    }

    // You can add buttons, sliders, etc. here
    ImGui::End();
  }

  auto
  SindriGui::GetLuaScripts() -> std::vector<std::filesystem::path>
  {
    std::vector<std::filesystem::path> scripts;
    for (const auto& entry : std::filesystem::directory_iterator("lua"))
    {
      if (entry.is_regular_file() && entry.path().extension() == ".lua")
      {
        scripts.push_back(entry.path()); // relative name
      }
    }
    return scripts;
  }

  void
  SindriGui::LuaScriptSelector()
  {
    // Combo Box
    if (ImGui::BeginCombo("Lua Script",
                          mSelectedScriptIndex >= 0 &&
                              mSelectedScriptIndex < mScripts.size()
                            ? mScripts[mSelectedScriptIndex].string().c_str()
                            : "Select..."))
    {
      for (int i = 0; i < mScripts.size(); ++i)
      {
        bool isSelected = (mSelectedScriptIndex == i);
        if (ImGui::Selectable(mScripts[i].string().c_str(), isSelected))
        {
          mSelectedScriptIndex = i;
        }
        if (isSelected)
        {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }

    // ImGui::SameLine();

    // Add Button
    if (ImGui::Button("Add layer"))
    {
      if (mSelectedScriptIndex >= 0 && mSelectedScriptIndex < mScripts.size())
      {
        // std::string selectedScript = mScripts[mSelectedScriptIndex];
        mTexturePipeline->AddLayer(mScripts[mSelectedScriptIndex]);
        // TODO: Do something with the selected script
        // std::cout << "Selected: " << selectedScript << std::endl;
      }
    }

    ImGui::SameLine();

    if (ImGui::Button("Refresh"))
    {
      mSelectedScriptIndex = 0;
      mScripts = GetLuaScripts();
    }
  }

  void
  SindriGui::GenerateTexture()
  {
    switch (mTextureSettings->Dimensions)
    {
      case TextureDimension::Texture1D:
        mTextureBuffer->Reserve(mTextureSettings->Resolution.x);
        break;
      case TextureDimension::Texture2D:
        mTextureBuffer->Reserve(mTextureSettings->Resolution.x,
                                mTextureSettings->Resolution.y);
        break;
      case TextureDimension::Texture3D:
        mTextureBuffer->Reserve(mTextureSettings->Resolution.x,
                                mTextureSettings->Resolution.y,
                                mTextureSettings->Resolution.z);
        break;
    }

    // mNoiseGenerator.RequestTextureFill();

    mExecutor->ExecutePipeline(*mTextureSettings);

    // mNoiseGenerator.FillTexture(mCompositionStack, mTextureSettings,
  }
  void
  SindriGui::Render(float deltaTime)
  {
    mWindow->NewFrame();
    RenderImGui(deltaTime);
    mWindow->EndFrame();
  }
}