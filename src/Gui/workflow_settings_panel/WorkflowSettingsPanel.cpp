#include "TextureTypes.hpp"
#include "pch.hpp"

#include "ImGuiHelper.hpp"
#include "WorkflowSettingsPanel.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <utility>

namespace Sindri
{
  WorkflowSettingsPanel::WorkflowSettingsPanel(
    std::shared_ptr<IWorkflowSettings> workflowSettingsEditor)
    : mWorkflowSettings(std::move(workflowSettingsEditor))
  {
  }

  void
  WorkflowSettingsPanel::Render()
  {
    /*#ifdef SINDRI_DEBUG_BUILD
        ImGui::SeparatorText("Debug");

        ImGui::Text("FPS: %.1f", mFps);
        ImGui::Text("Frame Time: %.2f ms", mMsPerFrame);

        static bool vsync = mWindow->IsVSync();
        if (ImGui::Checkbox("VSync", &vsync))
        {
          // SDL_GL_SetSwapInterval(mVsync ? 1 : 0);
          mWindow->SetVSync(vsync);
        }

        ImGui::Spacing();
    #endif*/

    ImGui::SeparatorText("Workflow Settings");

    static uint32_t seed = mWorkflowSettings->GetSeed();
    if (ImGui::InputScalar("Seed", ImGuiDataType_U32, &seed))
    {
      mWorkflowSettings->SetSeed(seed);
    }

    ImGui::SameLine();
    if (ImGui::Button("Random"))
    {
      mWorkflowSettings->RandomizeSeed();
    }

    static TextureDimension dimension = mWorkflowSettings->GetDimensions();

    if (ImGui::RadioButton("Texture 1D",
                           dimension == TextureDimension::Texture1D))
    {
      if (dimension != TextureDimension::Texture1D)
      {
        dimension = TextureDimension::Texture1D;
        mWorkflowSettings->SetDimensions(TextureDimension::Texture1D);
      }
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Texture 2D",
                           dimension == TextureDimension::Texture2D))
    {
      if (dimension != TextureDimension::Texture2D)
      {
        dimension = TextureDimension::Texture2D;
        mWorkflowSettings->SetDimensions(TextureDimension::Texture2D);
      }
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Texture 3D",
                           dimension == TextureDimension::Texture3D))
    {
      if (dimension != TextureDimension::Texture3D)
      {
        dimension = TextureDimension::Texture3D;
        mWorkflowSettings->SetDimensions(TextureDimension::Texture3D);
      }
    }

    // Set channel count
    static ChannelCount channelCount = mWorkflowSettings->GetChannelCount();
    if (ComboEnum("Channels", channelCount))
    {
      mWorkflowSettings->SetChannelCount(channelCount);
    }

    ImGui::Spacing();
    /*ImGui::SeparatorText("Preview Settings");

    mPreview->RenderSettings();*/

    /*if (mTexturePipeline->GetLayers().empty() || mExecutor->IsRunning())
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

    ImGui::SameLine();*/

    /*if (mTextureBuffer->GetData().empty() || mExecutor->IsRunning())
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

    mExporter->Render();*/
  }
}