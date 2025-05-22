#version 460 core

layout(location = 0) in vec3 aPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vWorldPos;
out vec3 vLocalPos;

void main() {
    vec4 worldPos = uModel * vec4(aPosition, 1.0);
    vLocalPos = aPosition;
    vWorldPos = worldPos.xyz;
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
