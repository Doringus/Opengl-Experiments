#version 450 core

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 fragmentPosition;

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

struct baseLight_t {
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
};

struct directionalLight_t {
    vec3 direction;
    baseLight_t baseLight;
};

uniform directionalLight_t directionalLight;

struct pointLight_t {
    vec3 position;
    baseLight_t baseLight;
    float constant;
    float linear;
    float exponent;
};

uniform pointLight_t pointLight;

out vec4 color;

vec4 calculateLightBase(vec3 lightDirection, baseLight_t baseLight) {
    vec3 s = normalize(lightDirection);
    vec3 viewDirection = normalize(-fragmentPosition);
    vec3 reflectDirection = reflect(-s, normal);
    // ambient
    vec3 ambient = material.ambient * baseLight.color * baseLight.ambientIntensity;
    // diffuse
    float diffuseComponent = max(dot(s, normal), 0.0);
    vec3 diffuse = baseLight.color * baseLight.diffuseIntensity * material.diffuse * diffuseComponent;
    // specular
    float specularComponent = pow(max(dot(reflectDirection, viewDirection), 0.0), material.shines);
    vec3 specular = baseLight.color * baseLight.specularIntensity * material.specular * specularComponent;
    vec3 resultColor = ambient + diffuse + specular + material.emission;
    return vec4(resultColor, 1.0);
}

void main() {
    /// for directional light
     color = calculateLightBase(directionalLight.direction, directionalLight.baseLight);
    /// for point light
  //  vec3 lightDirection = pointLight.position - position;
  //  vec4 pointLightColor = calculateLightBase(normalize(lightDirection), pointLight.baseLight);
   // float dist = length(lightDirection);
   // float attenuation = pointLight.constant + pointLight.linear * dist + pointLight.exponent * dist * dist;
    //color = pointLightColor / attenuation;
   // color = pointLightColor;
}