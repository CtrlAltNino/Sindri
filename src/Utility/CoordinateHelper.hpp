#include "TextureSettings/TextureSettings.hpp"
#include <glm/glm.hpp>

namespace Sindri
{
  // Converts a linear index into a coordinate in 1D, 2D, or 3D space
  auto
  IndexToCoord(int               index,
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
}