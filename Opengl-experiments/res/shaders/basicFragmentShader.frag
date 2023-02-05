#version 450 core

layout (location = 0) in vec3 inColor;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 fragmentPosition;

layout (binding = 0) uniform sampler2D textureSampler;

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
    float constant;
    float linear;
    float exponent;
    baseLight_t baseLight;
};

uniform pointLight_t pointLight;

struct spotLight_t {
    vec3 direction;
    float cutOffCos;
    pointLight_t point;
};

uniform spotLight_t spotLight;

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
    //  color = calculateLightBase(directionalLight.direction, directionalLight.baseLight);
    /// for point light
    //vec3 lightDirection = pointLight.position - fragmentPosition;
    //vec4 pointLightColor = calculateLightBase(lightDirection, pointLight.baseLight);
    //float dist = length(lightDirection);
    //float attenuation = pointLight.constant + pointLight.linear * dist + pointLight.exponent * dist * dist;
    //color = pointLightColor / attenuation;
    /// for spot light
    vec4 spotLightColor = calculateLightBase(spotLight.direction, spotLight.point.baseLight);
    vec3 lightDirection = normalize(spotLight.point.position - fragmentPosition);
    float dist = length(lightDirection);
    float spotFactor = dot(-lightDirection, spotLight.direction);
    if(spotFactor > spotLight.cutOffCos) {
        vec4 spotLightColor = calculateLightBase(lightDirection, spotLight.point.baseLight);
        float attenuation = spotLight.point.constant + spotLight.point.linear * dist + spotLight.point.exponent * dist * dist;
        color = (spotLightColor * (1.0 - (1.0 - spotFactor) * 1.0 / (1.0 - spotLight.cutOffCos))) / attenuation;
    } else {
        color = vec4(material.emission, 1.0);
    }
}