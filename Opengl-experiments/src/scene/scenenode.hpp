#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class GameObject;

struct transform_t {
	glm::vec3 worldPosition;
	glm::vec3 scale;
	double yaw, pitch, roll;
};

/*
 * TODO: make children position change
 *
 */

class SceneNode {
public:
	explicit SceneNode(const transform_t& transform) noexcept;

	SceneNode* createChild() noexcept;

	/* Node not manage object lifetime */
	void attachGameObject(GameObject* gameObject) noexcept;
	void setPosition(const glm::vec3& position) noexcept;
	void setPitch(double pitch) noexcept;
	void setYaw(double yaw) noexcept;
	void setRoll(double roll) noexcept;

	transform_t& getTransform() noexcept;
	const transform_t& getTransform() const noexcept;

private:
	transform_t m_Transform;
	GameObject* m_Object;
	std::vector<std::unique_ptr<SceneNode>> m_Children;
};