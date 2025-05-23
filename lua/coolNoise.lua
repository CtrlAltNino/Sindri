-- Define the exposed settings table
settings = {
    scale = 1.0
}

name = "Cool Noise"

-- Called for every pixel
function evaluate(x, y, z, seed)
    return math.sin(settings.scale * (x + y + z + seed));
end
