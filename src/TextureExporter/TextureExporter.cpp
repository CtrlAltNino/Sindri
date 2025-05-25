#include "pch.hpp"

#include "Gui/Helpers/ImGuiHelper.hpp"
#include "ImageWriting/PngWriter.hpp"
#include "TextureExporter.hpp"
#include <algorithm>
#include <imgui.h>
#include <magic_enum/magic_enum.hpp>
#include <nfd.hpp>

namespace Sindri
{
  TextureExporter::TextureExporter(
    std::shared_ptr<ITextureBuffer>  texture,
    std::shared_ptr<TextureSettings> textureSettings)
    : mTexture(std::move(texture))
    , mTextureSettings(std::move(textureSettings))
  {
  }

  void
  TextureExporter::Render()
  {
    ImGuiWindowFlags popupFlags = ImGuiWindowFlags_NoResize |
                                  ImGuiWindowFlags_NoMove |
                                  ImGuiWindowFlags_AlwaysAutoResize;

    if (ImGui::BeginPopupModal("Export##ExportModal", NULL, popupFlags))
    {
      const auto& caps = formatCaps.at(mExportSettings.format);

      ImGuiSelectableFlags selectableFlags =
        ImGuiSelectableFlags_DontClosePopups;

      // Format Combo
      if (ImGui::BeginCombo(
            "Format", magic_enum::enum_name(mExportSettings.format).data()))
      {
        for (auto fmt : magic_enum::enum_values<FileFormat>())
        {
          bool selected = (fmt == mExportSettings.format);
          if (ImGui::Selectable(magic_enum::enum_name(fmt).data(), selected, 0))
          {
            mExportSettings.format = fmt;
          }
          if (selected)
          {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      ImGui::Spacing();

      // Data Type Combo with compatibility
      // ImGui::Text("Data Type");
      if (ImGui::BeginCombo(
            "Data Type",
            magic_enum::enum_name(mExportSettings.dataType).data()))
      {
        for (auto type : magic_enum::enum_values<DataType>())
        {
          bool supported =
            (type == DataType::UNorm8 && caps.supportsUNorm8) ||
            (type == DataType::UNorm16 && caps.supportsUNorm16) ||
            (type == DataType::Float16 && caps.supportsFloat16) ||
            (type == DataType::Float32 && caps.supportsFloat32);

          if (!supported)
          {
            ImGui::BeginDisabled();
          }
          bool selected = (type == mExportSettings.dataType);
          if (ImGui::Selectable(
                magic_enum::enum_name(type).data(), selected, 0))
          {
            if (supported)
            {
              mExportSettings.dataType = type;
            }
          }
          if (!supported)
          {
            ImGui::SameLine();
            ImGui::TextDisabled(" (unsupported)");
            ImGui::EndDisabled();
          }
        }
        ImGui::EndCombo();
      }

      ImGui::Spacing();

      // Channels
      // ImGui::Text("Channels");
      if (ImGui::BeginCombo(
            "Channels", magic_enum::enum_name(mExportSettings.channels).data()))
      {
        for (auto ch : magic_enum::enum_values<ChannelCount>())
        {
          bool supported = std::ranges::find(caps.supportedChannels, ch) !=
                           caps.supportedChannels.end();
          if (!supported)
          {
            ImGui::BeginDisabled();
          }
          bool selected = (ch == mExportSettings.channels);
          if (ImGui::Selectable(magic_enum::enum_name(ch).data(), selected, 0))
          {
            if (supported)
            {
              mExportSettings.channels = ch;
            }
          }
          if (!supported)
          {
            ImGui::SameLine();
            ImGui::TextDisabled(" (unsupported)");
            ImGui::EndDisabled();
          }
        }
        ImGui::EndCombo();
      }

      ImGui::Spacing();

      // Compression
      {
        // ImGui::Text("Compression");
        if (!caps.supportsCompression)
        {
          ImGui::BeginDisabled();
        }
        if (ImGui::BeginCombo(
              "Compression",
              magic_enum::enum_name(mExportSettings.compression).data()))
        {
          for (auto c : magic_enum::enum_values<CompressionType>())
          {
            bool selected = (c == mExportSettings.compression);
            if (ImGui::Selectable(magic_enum::enum_name(c).data(), selected, 0))
            {
              mExportSettings.compression = c;
            }
            if (selected)
            {
              ImGui::SetItemDefaultFocus();
            }
          }
          ImGui::EndCombo();
        }
        if (!caps.supportsCompression)
        {
          // ImGui::SetTooltip("Compression not supported by this format");
          ImGui::EndDisabled();
        }
      }

      ImGui::Spacing();

      {
        // ImGui::InputText("Path", )
        // ImGui::Text("%s", mExportSettings.path.string().c_str());
        InputTextString("Path", mExportSettings.path);
        ImGui::SameLine();
        if (ImGui::Button("Browse"))
        {
          // initialize NFD
          NFD::Guard nfdGuard;
          // auto-freeing memory
          NFD::UniquePath outPath;
          std::string     formatName =
            std::string(magic_enum::enum_name(mExportSettings.format));
          nfdfilteritem_t filterItem[1] = {
            { formatName.c_str(),
              formatFileExtensions.at(mExportSettings.format).c_str() }
          };
          // show the dialog
          // nfdresult_t result = NFD::PickFolder(outPath);
          nfdresult_t result = NFD::SaveDialog(outPath, filterItem, 1);

          if (result == NFD_OKAY)
          {
            // newProjectPath = std::string(outPath.get());
            mExportSettings.path = std::string(outPath.get());
          }
          else if (result == NFD_CANCEL)
          {
            // puts("User pressed cancel.");
          }
          else
          {
            // printf("Error: %s\n", NFD_GetError());
          }
        }
      }

      ImGui::Spacing();

      if (ImGui::Button("Close"))
      {
        ImGui::CloseCurrentPopup();
      }

      ImGui::SameLine();

      if (ImGui::Button("Export"))
      {
        Export();
      }

      ImGui::EndPopup();
    }
  }

  void
  TextureExporter::Export()
  {
    switch (mExportSettings.format)
    {
      case Sindri::FileFormat::PNG:
        PngWriter::WritePng(mTexture->GetData(),
                            mTexture->GetWidth(),
                            mTexture->GetHeight(),
                            mExportSettings.channels,
                            mExportSettings.dataType,
                            mExportSettings.path);
    }
  }
}