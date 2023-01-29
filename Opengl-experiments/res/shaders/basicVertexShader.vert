#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
//layout (location = 3) in vec3 normal;

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec2 outTexCoord;
//layout (location = 2) out vec3 outNormal;
//layout (location = 3) out vec3 outFragmentPosition;

layout (location = 3) uniform mat4 modelToWorldMatrix;

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};


void main() {
    gl_Position = modelToWorldMatrix * vec4(position, 1.0);
    outColor = color;
    outTexCoord = texCoord;
 //   outNormal = normal;
   // outFragmentPosition = vec3()
}