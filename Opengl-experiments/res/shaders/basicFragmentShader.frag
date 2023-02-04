#version 450 core

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 position;

layout (binding = 0) uniform sampler2D textureSampler;
uniform vec3 cameraPosition;

struct material_t {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shines;
};

uniform material_t material;

struct directionalLight_t {
    vec3 direction;
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

uniform directionalLight_t directionalLight;

out vec4 color;

void main() {
    vec3 invLightDirection = -directionalLight.direction;
    /// Calculate directional light
    // ambient
    vec3 ambient = material.ambient * directionalLight.color * directionalLight.ambientIntensity;
    // diffuse
    float nDotL = max(dot(normal, invLightDirection), 0.0);
    vec3 diffuse = directionalLight.color * directionalLight.diffuseIntensity * material.diffuse * nDotL;
    // specular 
    vec3 viewDirection = normalize(cameraPosition - position);
    vec3 reflectDirection = reflect(invLightDirection, normal);
    vec3 specular = vec3(1.0);
    float vDotR = max(dot(viewDirection, reflectDirection), 0.0);
    specular = directionalLight.color * directionalLight.specularIntensity * material.specular * pow(vDotR, material.shines);
    vec3 resultColor = ambient + diffuse + specular + material.emission;
    
   // color = texture(textureSampler, textureCoord) * vec4(resultColor, 1.0f);
    color = vec4(resultColor, 1.0);
}