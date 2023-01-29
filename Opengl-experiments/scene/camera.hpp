#pragma once

#include <glm/mat4x4.hpp>

#include "gameobject.hpp"

class Camera final : public GameObject {
public:
	Camera(SceneNode* parent, const glm::mat4 projectionMatrix) noexcept;

	glm::mat4 calculateCameraMatrix() const noexcept;
	const glm::mat4& getViewMatrix() const noexcept;
	const glm::mat4& getProjectionMatrix() const noexcept;
	const glm::vec3& getFrontVec() const noexcept;
	const glm::vec3& getUpVec() const noexcept;

	void update();
private:
	glm::vec3 m_Front, m_Up;
	glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
};