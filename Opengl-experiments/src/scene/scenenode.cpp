#include "scenenode.hpp"

#include "gameobject.hpp"

SceneNode::SceneNode(const transform_t& transform) noexcept: m_Transform(transform), m_Object(nullptr) {
	
}

SceneNode* SceneNode::createChild() noexcept {
	m_Children.push_back(std::make_unique<SceneNode>(m_Transform));
	return m_Children.back().get();
}

void SceneNode::attachGameObject(GameObject* gameObject) noexcept {
	m_Object = gameObject;
	m_Object->setParent(this);
}

void SceneNode::setPosition(const glm::vec3& position) noexcept {
	m_Transform.worldPosition = position;
}

void SceneNode::setPitch(double pitch) noexcept {
	m_Transform.pitch = pitch;
}

void SceneNode::setYaw(double yaw) noexcept {
	m_Transform.yaw = yaw;
}

void SceneNode::setRoll(double roll) noexcept {
	m_Transform.roll = roll;
}

transform_t& SceneNode::getTransform() noexcept {
	return m_Transform;
}

const transform_t& SceneNode::getTransform() const noexcept {
	return m_Transform;
}
