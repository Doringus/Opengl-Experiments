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
    float shines;
};

uniform material_t material;

struct directionalLight_t {
    vec3 lightDirection;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

uniform directionalLight_t directionalLight;

out vec4 color;

void main() {
    vec3 invLightDirection = directionalLight.lightDirection;
    /// Calculate directional light
    // ambient
    vec3 ambient = directionalLight.ambient * material.ambient;
    // diffuse
    float nDotL = max(dot(normal, invLightDirection), 0.0);
    vec3 diffuse = directionalLight.diffuse * material.diffuse * nDotL;
    // specular
   // vec3 specular = lSpecular * mSpecular * pow(max(dot())) 
    vec3 viewDirection = normalize(cameraPosition - position);
    vec3 reflectDirection = reflect(invLightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shines);
    vec3 specular = directionalLight.specular * material.specular * spec;
    vec3 resultColor = diffuse + ambient + specular;
    
   // color = texture(textureSampler, textureCoord) * vec4(resultColor, 1.0f);
   color = vec4(resultColor, 1.0);
}