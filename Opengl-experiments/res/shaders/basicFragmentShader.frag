#version 450 core
#extension GL_ARB_bindless_texture : require

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
layout(bindless_sampler) uniform sampler2D textureSampler;

out vec4 color;

void main() {
    color = texture(textureSampler, textureCoord) * vec4(inColor, 1.0f);
}