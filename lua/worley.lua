Settings = {
    cell_count = 4,  -- Zoom level
    inverted = false -- Whether to invert brightness (1.0 - distance)
}

function Setup(seed)
    -- No setup needed for this implementation
end

-- 2D hash function to generate pseudo-random vec2 from integer coordinates
local function rand2D(ix, iy)
    local dot1 = ix * 127.1 + iy * 311.7
    local dot2 = ix * 269.5 + iy * 183.3

    local sin1 = math.sin(dot1) * 43758.5453
    local sin2 = math.sin(dot2) * 43758.5453

    return {
        sin1 - math.floor(sin1),
        sin2 - math.floor(sin2)
    }
end

local function rand3D(ix, iy, iz)
    local dot1 = ix * 127.1 + iy * 311.7 + iz * 74.7
    local dot2 = ix * 269.5 + iy * 183.3 + iz * 246.1
    local dot3 = ix * 113.5 + iy * 271.9 + iz * 124.6

    local sin1 = math.sin(dot1) * 43758.5453
    local sin2 = math.sin(dot2) * 43758.5453
    local sin3 = math.sin(dot3) * 43758.5453

    return {
        sin1 - math.floor(sin1),
        sin2 - math.floor(sin2),
        sin3 - math.floor(sin3)
    }
end

function Evaluate2D(x, y, seed)
    local count = Settings.cell_count
    local px = x * count
    local py = y * count

    local ix = math.floor(px)
    local iy = math.floor(py)
    local fx = px - ix
    local fy = py - iy

    local min_dist = math.huge

    for dy = -1, 1 do
        for dx = -1, 1 do
            local cx = ix + dx
            local cy = iy + dy

            local r = rand2D(cx, cy)

            local feature_x = dx + r[1]
            local feature_y = dy + r[2]

            local dx2 = fx - feature_x
            local dy2 = fy - feature_y

            local dist = math.sqrt(dx2 * dx2 + dy2 * dy2)
            if dist < min_dist then
                min_dist = dist
            end
        end
    end

    -- Optional normalization (remove if you prefer raw distances)
    --min_dist = math.min(min_dist / math.sqrt(2), 1.0)

    -- Inversion toggle
    if Settings.inverted then
        return 1.0 - min_dist
    else
        return min_dist
    end
end

function Evaluate3D(x, y, z, seed)
    local count = Settings.cell_count
    local px = x * count
    local py = y * count
    local pz = z * count

    local ix = math.floor(px)
    local iy = math.floor(py)
    local iz = math.floor(pz)
    local fx = px - ix
    local fy = py - iy
    local fz = pz - iz

    local min_dist = math.huge

    for dz = -1, 1 do
        for dy = -1, 1 do
            for dx = -1, 1 do
                local cx = ix + dx
                local cy = iy + dy
                local cz = iz + dz

                local r = rand3D(cx, cy, cz)

                local feature_x = dx + r[1]
                local feature_y = dy + r[2]
                local feature_z = dz + r[3]

                local dx2 = fx - feature_x
                local dy2 = fy - feature_y
                local dz2 = fz - feature_z

                local dist = math.sqrt(dx2 * dx2 + dy2 * dy2 + dz2 * dz2)
                if dist < min_dist then
                    min_dist = dist
                end
            end
        end
    end

    -- Optional normalization (remove if you prefer raw distances)
    --min_dist = math.min(min_dist / math.sqrt(2), 1.0)

    -- Inversion toggle
    if Settings.inverted then
        return 1.0 - min_dist
    else
        return min_dist
    end
end
