#pragma once

#include "TextureExporter.hpp"
#include <spng.h>

namespace Sindri
{
  class PngWriter
  {
  public:
    static void
    WritePng(const std::vector<float>&    data,
             int                          width,
             int                          height,
             ChannelCount                 format,
             DataType                     depth,
             const std::filesystem::path& path)
    {
      const int    channels = static_cast<int>(format);
      const size_t expected_size =
        static_cast<size_t>(width) * height * channels;

      std::cout << "Data length: " << data.size() << std::endl;

      if (data.size() != expected_size)
        throw std::runtime_error(
          "Input data size does not match width * height * channels");

      // Convert float [0.0, 1.0] to uint8_t or uint16_t
      std::vector<uint8_t>  buffer8;
      std::vector<uint16_t> buffer16;

      void*  final_data = nullptr;
      size_t stride = width * channels * ((depth == DataType::UNorm8) ? 1 : 2);

      if (depth == DataType::UNorm8)
      {
        buffer8.resize(expected_size);
        for (size_t i = 0; i < expected_size; ++i)
          buffer8[i] = static_cast<uint8_t>(
            std::clamp(data[i], 0.0f, 1.0f) * 255.0f + 0.5f);
        final_data = buffer8.data();
      }
      else
      {
        buffer16.resize(expected_size);
        for (size_t i = 0; i < expected_size; ++i)
          buffer16[i] = static_cast<uint16_t>(
            std::clamp(data[i], 0.0f, 1.0f) * 65535.0f + 0.5f);
        final_data = buffer16.data();
      }

      // Create encoder context
      spng_ctx* ctx = spng_ctx_new(SPNG_CTX_ENCODER);
      if (!ctx) throw std::runtime_error("Failed to create spng context");

      std::vector<uint8_t> png_output;
      spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);
      spng_set_png_buffer(ctx, nullptr, 0); // Use dynamic memory

      // Set IHDR
      spng_ihdr ihdr{};
      ihdr.width = width;
      ihdr.height = height;
      ihdr.bit_depth = (depth == DataType::UNorm8) ? 8 : 16;

      switch (format)
      {
        case ChannelCount::R:
          ihdr.color_type = SPNG_COLOR_TYPE_GRAYSCALE;
          break;
        case ChannelCount::RG:
          ihdr.color_type = SPNG_COLOR_TYPE_GRAYSCALE_ALPHA;
          break;
        case ChannelCount::RGB:
          ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR;
          break;
        case ChannelCount::RGBA:
          ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;
          break;
        default:
          spng_ctx_free(ctx);
          throw std::runtime_error("Invalid PNGFormat");
      }

      ihdr.compression_method = 0;
      ihdr.filter_method = 0;
      ihdr.interlace_method = 0;

      if (spng_set_ihdr(ctx, &ihdr))
      {
        throw std::runtime_error("Failed to set IHDR");
      }

      if (int err = spng_encode_image(
            ctx, final_data, expected_size, SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE))
      {
        spng_ctx_free(ctx);
        std::cout << spng_strerror(err) << std::endl;
        throw std::runtime_error(std::string("Failed to encode PNG: ") +
                                 std::string(spng_strerror(err)));
      }

      size_t png_size;
      void*  png_buf = spng_get_png_buffer(ctx, &png_size, nullptr);
      if (!png_buf)
      {
        spng_ctx_free(ctx);
        throw std::runtime_error("Failed to get PNG buffer");
      }

      std::ofstream out(path, std::ios::binary);
      if (!out)
      {
        spng_ctx_free(ctx);
        // spng_free_png_buffer(ctx, png_buf);
        free(png_buf);
        throw std::runtime_error("Failed to open output file");
      }

      out.write(reinterpret_cast<char*>(png_buf), png_size);
      out.close();

      //   spng_free_png_buffer(ctx, png_buf);
      free(png_buf);
      spng_ctx_free(ctx);
    }
  };
}