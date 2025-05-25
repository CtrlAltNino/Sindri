#pragma once

#include "TextureExporter.hpp"

namespace Sindri
{
  class TgaWriter
  {
  public:
    static void
    WriteTga(const std::vector<float>&    data,
             int                          width,
             int                          height,
             ChannelCount                 format,
             const std::filesystem::path& path)
    {
      if (data.size() != static_cast<size_t>(width * height * 3))
        throw std::runtime_error("Invalid RGB data size");

      std::ofstream out(path, std::ios::binary);
      if (!out) throw std::runtime_error("Failed to open TGA output file");

      uint8_t header[18] = {};
      header[2] = 2; // Uncompressed RGB
      header[12] = width & 0xFF;
      header[13] = (width >> 8) & 0xFF;
      header[14] = height & 0xFF;
      header[15] = (height >> 8) & 0xFF;
      header[16] = 24;   // bits per pixel
      header[17] = 0x20; // top-left origin

      out.write(reinterpret_cast<char*>(header), sizeof(header));

      // TGA expects BGR order, so swap R and B
      for (int i = 0; i < width * height; ++i)
      {
        out.put(data[i * 3 + 2]); // B
        out.put(data[i * 3 + 1]); // G
        out.put(data[i * 3 + 0]); // R
      }
    }
  };
}