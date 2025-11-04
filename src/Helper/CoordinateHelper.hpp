#pragma once

#include "TextureTypes.hpp"
#include <glm/glm.hpp>

namespace Sindri
{
  using UVCoordinate = std::variant<float, glm::vec2, glm::vec3>;

  // Converts a linear index into a coordinate in 1D, 2D, or 3D space
  static auto
  IndexToCoord(size_t            index,
               const glm::ivec3& resolution,
               TextureDimension  dimension) -> glm::ivec3
  {
    assert(index >= 0);

    switch (dimension)
    {
      case TextureDimension::Texture1D:
        {
          assert(resolution.x > 0);
          return { index % resolution.x, 0, 0 };
        }

      case TextureDimension::Texture2D:
        {
          assert(resolution.x > 0 && resolution.y > 0);
          int x = index % resolution.x;
          int y = (index / resolution.x) % resolution.y;
          return { x, y, 0 };
        }

      case TextureDimension::Texture3D:
        {
          assert(resolution.x > 0 && resolution.y > 0 && resolution.z > 0);
          int x = index % resolution.x;
          int y = (index / resolution.x) % resolution.y;
          int z = index / (resolution.x * resolution.y);
          return { x, y, z };
        }

      default: return glm::ivec3(0); // fallback, should not happen
    }
  }

  static auto
  CoordToIndex(const glm::ivec3& coordinate,
               const glm::ivec3& resolution,
               TextureDimension  dimension) -> int
  {
    switch (dimension)
    {
      case TextureDimension::Texture1D:
        {
          assert(coordinate.x < resolution.x);
          return coordinate.x;
        }

      case TextureDimension::Texture2D:
        {
          assert(coordinate.x < resolution.x && coordinate.y < resolution.y);
          return (coordinate.y * resolution.x) + coordinate.x;
        }

      case TextureDimension::Texture3D:
        {
          assert(coordinate.x < resolution.x && coordinate.y < resolution.y &&
                 coordinate.z < resolution.z);
          return (coordinate.z * resolution.x * resolution.y) +
                 (coordinate.y * resolution.x) + coordinate.x;
        }

      default: return 0; // fallback, should not happen
    }
  }
}