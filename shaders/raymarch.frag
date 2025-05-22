#version 460 core

in vec3 vWorldPos;
in vec3 vLocalPos;
out vec4 FragColor;

uniform mat4 uModel;
uniform vec3 uCameraPos;
uniform float uStepSize; // Suggested range: 0.001 – 0.02
uniform sampler3D uVolume;
uniform float uDensityFactor;
uniform int uMaxSteps;

void main() {
    vec3 rayDir = (inverse(uModel) * vec4(normalize(vWorldPos - uCameraPos), 1.0)).xyz;
    vec3 rayOrigin = vLocalPos;

    // Start marching
    //const int maxSteps = 512;
    vec3 pos = rayOrigin;
    float t = 0.0;

    vec4 accumulatedColor = vec4(0.0);
    float accumulatedDensity = 0.0;
    for (int i = 0; i < uMaxSteps; ++i) {
        vec3 samplePos = rayOrigin + rayDir * t;

        // Volume is assumed to be in [-1,1]^3, remap to [0,1]^3
        vec3 texCoord = samplePos * 0.5 + 0.5;

        // Stop if ray exits the volume
        if (any(lessThan(texCoord, vec3(0.0))) || any(greaterThan(texCoord, vec3(1.0))))
          break;

        // Sample density
        float density = texture(uVolume, texCoord).r;
        accumulatedDensity += density * uStepSize * uDensityFactor;

        // Simple front-to-back alpha blending
        /*float alpha = density * 0.05; // Adjust density influence
        vec3 color = vec3(density);   // Grayscale

        accumulatedColor.rgb += (1.0 - accumulatedColor.a) * alpha * color;
        accumulatedColor.a += (1.0 - accumulatedColor.a) * alpha;*/

        if (accumulatedColor.a >= 0.95)
           break;

        t += uStepSize;
    }

    FragColor = vec4(1,1,1,accumulatedDensity);
}
