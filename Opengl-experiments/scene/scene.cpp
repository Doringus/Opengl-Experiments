#include "scene.hpp"

Scene::Scene() noexcept: m_Root({ .worldPosition = glm::vec3(0), .scale = glm::vec3(1), .yaw = 0, .pitch = 0, .roll = 0}) {
	
}

SceneNode& Scene::getRootNode() noexcept {
	return m_Root;
}

const SceneNode& Scene::getRootNode() const noexcept {
	return m_Root;
}
