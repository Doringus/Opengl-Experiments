#version 450 core
//#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
//layout (location = 2) in vec3 normal;

//layout (bindless_sampler) uniform sampler2D textureSampler;
layout (binding = 0) uniform sampler2D textureSampler;
layout (location = 0) uniform vec3 lightColor;
//layout (location = 1) uniform vec2 lightPostion;

out vec4 color;

void main() {
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 resultColor = ambient * inColor;
    color = texture(textureSampler, textureCoord) * vec4(resultColor, 1.0f);
}