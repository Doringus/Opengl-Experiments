#include "camera.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "scenenode.hpp"

Camera::Camera(SceneNode* parent, const glm::mat4 projectionMatrix) noexcept
	: GameObject(parent), m_ProjectionMatrix(projectionMatrix), m_Up(0.f, 1.f, 0.f), m_Front(0.f, 0.f, 1.f) {
	
}

glm::mat4 Camera::calculateCameraMatrix() const noexcept {
	return m_ProjectionMatrix * m_ViewMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept {
	return m_ViewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const noexcept {
	return m_ProjectionMatrix;
}

const glm::vec3& Camera::getFrontVec() const noexcept {
	return m_Front;
}

const glm::vec3& Camera::getUpVec() const noexcept {
	return m_Up;
}

void Camera::update() {
	const double yaw = m_Parent->getTransform().yaw;
	const double pitch = m_Parent->getTransform().pitch;
	const glm::vec3 position = m_Parent->getTransform().worldPosition;
	m_Front = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
						   sin(glm::radians(pitch)),
						   sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	m_Front = glm::normalize(m_Front);
	/// TODO: refactor up vector
	m_ViewMatrix = glm::lookAt(position, position + m_Front, m_Up);
}
