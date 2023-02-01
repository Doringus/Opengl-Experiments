#version 450 core

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 position;

layout (binding = 0) uniform sampler2D textureSampler;
layout (location = 0) uniform vec3 lightColor;
layout (location = 1) uniform vec3 cameraPosition;

out vec4 color;

void main() {
    // hardcode all material params
    vec3 mAmbient = vec3(1.0, 0.5, 0.3);
    vec3 mDiffuse = vec3(1.0, 0.5, 0.3);
    vec3 mSpecular = vec3(0.5, 0.5, 0.5);
    float mShiness = 2.3;
    // hardcode all directional light params
    vec3 lightDirection = vec3(0.0, 0.0, 1.0);
    vec3 invLightDirection = -lightDirection;
    vec3 lightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 lAmbient = vec3(0.2, 0.2, 0.2);
    vec3 lDiffuse = vec3(1.0, 1.0, 1.0);
    vec3 lSpecular = vec3(1.0, 1.0, 1.0);

    /// Calculate directional light
    // ambient
    vec3 ambient = lAmbient * mAmbient;
    // diffuse
    float nDotL = max(dot(normal, invLightDirection), 0.0);
    vec3 diffuse = lDiffuse * mDiffuse * nDotL;
    // specular
   // vec3 specular = lSpecular * mSpecular * pow(max(dot())) 
    vec3 viewDirection = normalize(cameraPosition - position);
    vec3 reflectDirection = reflect(invLightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), mShiness);
    vec3 specular = lSpecular * mSpecular * spec;

    vec3 resultColor = diffuse + ambient + specular;
    
   // color = texture(textureSampler, textureCoord) * vec4(resultColor, 1.0f);
   color = vec4(resultColor, 1.0);
}