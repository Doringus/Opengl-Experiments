#pragma once

class SceneNode;

class GameObject {
public:
	GameObject(SceneNode* parent) noexcept : m_Parent(parent) {}
protected:
	SceneNode* m_Parent;
};