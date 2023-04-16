#pragma once

#include <glm/vec3.hpp>

struct baseLight_t {
	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;
};

struct directionalLight_t {
	glm::vec3 direction;
	baseLight_t baseLight;
};

struct pointLight_t {
	glm::vec3 position;
	float constant;
	float linear;
	float exponent;
	baseLight_t baseLight;
};

struct spotLight_t {
	glm::vec3 direction;
	float cutOffAngle;
	pointLight_t point;
};

#include "program.hpp"

static void bindDirectionalLight(const directionalLight_t& light, Program& program) {
	program.setUniform("directionalLight.direction", light.direction);
	program.setUniform("directionalLight.baseLight.color", light.baseLight.color);
	program.setUniform("directionalLight.baseLight.ambientIntensity", light.baseLight.ambientIntensity);
	program.setUniform("directionalLight.baseLight.diffuseIntensity", light.baseLight.diffuseIntensity);
	program.setUniform("directionalLight.baseLight.specularIntensity", light.baseLight.specularIntensity);
}

static void bindPointLight(const pointLight_t& light, Program& program) {
	program.setUniform("pointLight.position", light.position);
	program.setUniform("pointLight.baseLight.color", light.baseLight.color);
	program.setUniform("pointLight.baseLight.ambientIntensity", light.baseLight.ambientIntensity);
	program.setUniform("pointLight.baseLight.diffuseIntensity", light.baseLight.diffuseIntensity);
	program.setUniform("pointLight.baseLight.specularIntensity", light.baseLight.specularIntensity);
	program.setUniform("pointLight.constant", light.constant);
	program.setUniform("pointLight.linear", light.linear);
	program.setUniform("pointLight.exponent", light.exponent);
}

static void bindSpotLight(const spotLight_t& light, Program& program) {
	program.setUniform("spotLight.direction", light.direction);
	program.setUniform("spotLight.cutOffCos", glm::cos(glm::radians(light.cutOffAngle)));
	program.setUniform("spotLight.point.position", light.point.position);
	program.setUniform("spotLight.point.baseLight.color", light.point.baseLight.color);
	program.setUniform("spotLight.point.baseLight.ambientIntensity", light.point.baseLight.ambientIntensity);
	program.setUniform("spotLight.point.baseLight.diffuseIntensity", light.point.baseLight.diffuseIntensity);
	program.setUniform("spotLight.point.baseLight.specularIntensity", light.point.baseLight.specularIntensity);
	program.setUniform("spotLight.point.constant", light.point.constant);
	program.setUniform("spotLight.point.linear", light.point.linear);
	program.setUniform("spotLight.point.exponent", light.point.exponent);
}