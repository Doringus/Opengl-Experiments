#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out VS_OUT {
    vec3 color;
    vec3 normal;
    vec3 fragmentPosition;
    vec2 texCoord;
} vs_out;

layout (location = 0) uniform mat4 MVP;
layout (location = 1) uniform mat4 modelViewMatrix;
layout (location = 2) uniform mat3 normalMatrix;


out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};


void main() {
    gl_Position = MVP * vec4(position, 1.0);
    vs_out.color = color;
    vs_out.texCoord = texCoord;
    vs_out.normal = normalize(normalMatrix * normal); // calc n in view space
    vs_out.fragmentPosition = vec3(modelViewMatrix * vec4(position, 1.0));
}