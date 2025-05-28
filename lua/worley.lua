Settings = {
    Cell_Count = 4, -- Zoom level
    Jitter = 1.0,
    Invert = false  -- Whether to invert brightness (1.0 - distance)
}

Name = "Worley Noise"

local feature_points = {}

function Setup(seed)
    -- No setup needed for this implementation
    math.randomseed(seed)
    local count = Settings.Cell_Count

    for z = 0, count - 1 do
        feature_points[z] = {}
        for y = 0, count - 1 do
            feature_points[z][y] = {}
            for x = 0, count - 1 do
                -- Generate a pseudo-random point inside the cell
                local jitter = Settings.Jitter

                -- Wrap the positions into [0, count) domain to preserve tileability
                feature_points[z][y][x] = {
                    math.random(),
                    math.random(),
                    math.random()
                }
            end
        end
    end
end

function Evaluate2D(x, y)
    local count = Settings.Cell_Count

    -- Scaled coordinate from [0, 1] to [0, cell_count]
    local px = x * count
    local py = y * count

    -- Feature point indices
    local ix = math.floor(px)
    local iy = math.floor(py)

    -- Relative coordinate in the cell [0, 1]
    local fx = px - ix
    local fy = py - iy

    local min_dist = math.huge

    for dy = -1, 1 do
        for dx = -1, 1 do
            -- The current cell index, with wrapping
            local cx = (ix + dx) % count
            local cy = (iy + dy) % count

            -- Feature point to compare
            local feature = feature_points[0][cy][cx]

            -- Current feature offsetted
            local feature_offset = { feature[1] + dx, feature[2] + dy };

            local diff_x = fx - feature_offset[1]
            local diff_y = fy - feature_offset[2]

            local distance = math.sqrt(diff_x * diff_x + diff_y * diff_y)

            if distance < min_dist then
                min_dist = distance
            end
        end
    end

    local color = min_dist

    if Settings.Invert then
        color = 1.0 - color
    end

    return color
end

function Evaluate3D(x, y, z)
    local count = Settings.Cell_Count

    -- Scaled coordinate from [0, 1] to [0, cell_count]
    local px = x * count
    local py = y * count
    local pz = z * count

    -- Feature point indices
    local ix = math.floor(px)
    local iy = math.floor(py)
    local iz = math.floor(pz)

    -- Relative coordinate in the cell [0, 1]
    local fx = px - ix
    local fy = py - iy
    local fz = pz - iz

    local min_dist = math.huge

    for dz = -1, 1 do
        for dy = -1, 1 do
            for dx = -1, 1 do
                -- The current cell index, with wrapping
                local cx = (ix + dx) % count
                local cy = (iy + dy) % count
                local cz = (iz + dz) % count

                -- Feature point to compare
                local feature = feature_points[cz][cy][cx]

                -- Current feature offsetted
                local feature_offset = { feature[1] + dx, feature[2] + dy, feature[3] + dz };

                local diff_x = fx - feature_offset[1]
                local diff_y = fy - feature_offset[2]
                local diff_z = fz - feature_offset[3]

                local distance = math.sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z)

                if distance < min_dist then
                    min_dist = distance
                end
            end
        end
    end

    local color = min_dist

    if Settings.Invert then
        color = 1.0 - color
    end

    return color
end
