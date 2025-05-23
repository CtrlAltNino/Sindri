#pragma once

#include "ProceduralTexture.hpp"
#include "TextureSettings/TextureSettings.hpp"

namespace Sindri
{
  enum class FileFormat : uint8_t
  {
    PNG,
    TGA,
    EXR,
    HDR,
    DDS,
    KTX,
    KTX2
  };

  enum class DataType
  {
    UNorm8,
    UNorm16,
    Float16,
    Float32
  };
  enum class ChannelCount
  {
    R = 1,
    RG = 2,
    RGB = 3,
    RGBA = 4
  };
  enum class CompressionType
  {
    None,
    BC1,
    BC3,
    BC4,
    BC5,
    BC6H,
    BC7,
    ASTC
  };

  struct ExportSettings
  {
    FileFormat      format = FileFormat::PNG;
    DataType        dataType = DataType::Float32;
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

  class TextureExporter
  {
  private:
    ExportSettings                     mExportSettings;
    std::shared_ptr<ProceduralTexture> mTexture;
    std::shared_ptr<TextureSettings>   mTextureSettings;

    void
    Export();

  public:
    TextureExporter(std::shared_ptr<ProceduralTexture> texture,
                    std::shared_ptr<TextureSettings>   textureSettings);

    void
    Render();
  };
}