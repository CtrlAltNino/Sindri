#pragma once

#include "ITextureBuffer.hpp"
#include "ITextureExporter.hpp"
#include "Texture/TextureTypes.hpp"
#include "WorkflowSettings/WorkflowSettings.hpp"

namespace Sindri
{
  struct ExportSettings
  {
    FileFormat      format = FileFormat::PNG;
    DataType        dataType = DataType::UNorm8;
    ChannelCount    channels = ChannelCount::RGBA;
    CompressionType compression = CompressionType::None;
    std::string     path;
  };

  struct FormatCapabilities
  {
    bool                      supportsUNorm8;
    bool                      supportsUNorm16;
    bool                      supportsFloat16;
    bool                      supportsFloat32;
    std::vector<ChannelCount> supportedChannels;
    bool                      supportsCompression;
  };

  const std::unordered_map<FileFormat, std::string> formatFileExtensions = {
    { FileFormat::PNG, "png" },  { FileFormat::PNG, "tga" },
    { FileFormat::PNG, "exr" },  { FileFormat::PNG, "hdr" },
    { FileFormat::PNG, "dds" },  { FileFormat::PNG, "ktx" },
    { FileFormat::PNG, "ktx2" },
  };

  const std::unordered_map<FileFormat, FormatCapabilities> formatCaps = {
    { FileFormat::PNG,
      { .supportsUNorm8 = true,
        .supportsUNorm16 = false,
        .supportsFloat16 = false,
        .supportsFloat32 = false,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RG,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = false } },
    { FileFormat::TGA,
      { .supportsUNorm8 = true,
        .supportsUNorm16 = false,
        .supportsFloat16 = false,
        .supportsFloat32 = false,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = false } },
    { FileFormat::EXR,
      { .supportsUNorm8 = false,
        .supportsUNorm16 = false,
        .supportsFloat16 = true,
        .supportsFloat32 = true,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RG,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = false } },
    { FileFormat::HDR,
      { .supportsUNorm8 = false,
        .supportsUNorm16 = false,
        .supportsFloat16 = false,
        .supportsFloat32 = true,
        .supportedChannels = { ChannelCount::RGB },
        .supportsCompression = false } },
    { FileFormat::DDS,
      { .supportsUNorm8 = true,
        .supportsUNorm16 = false,
        .supportsFloat16 = false,
        .supportsFloat32 = false,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = true } },
    { FileFormat::KTX,
      { .supportsUNorm8 = true,
        .supportsUNorm16 = true,
        .supportsFloat16 = true,
        .supportsFloat32 = true,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RG,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = true } },
    { FileFormat::KTX2,
      { .supportsUNorm8 = true,
        .supportsUNorm16 = true,
        .supportsFloat16 = true,
        .supportsFloat32 = true,
        .supportedChannels = { ChannelCount::R,
                               ChannelCount::RG,
                               ChannelCount::RGB,
                               ChannelCount::RGBA },
        .supportsCompression = true } },
  };

  class TextureExporter : public ITextureExporter
  {
  private:
    ExportSettings                    mExportSettings;
    std::shared_ptr<ITextureBuffer>   mTexture;
    std::shared_ptr<WorkflowSettings> mWorkflowSettings;

    void
    Export();

  public:
    TextureExporter(std::shared_ptr<ITextureBuffer>   texture,
                    std::shared_ptr<WorkflowSettings> workflowSettings);

    void
    Render() override;
  };
}