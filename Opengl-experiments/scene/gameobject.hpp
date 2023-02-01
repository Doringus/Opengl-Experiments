#pragma once

#include <optional>

class SceneNode;

class GameObject {
public:
	virtual ~GameObject() = default;
	GameObject(SceneNode* parent = nullptr) noexcept {
		setParent(parent);
	}
	
	void setParent(SceneNode* parent) noexcept {
		if (parent != nullptr) {
			m_Parent = parent;
		} else {
			m_Parent = std::nullopt;
		}
	}

	const std::optional<SceneNode*>& getParent() const noexcept {
		return m_Parent;
	}

private:
	std::optional<SceneNode*> m_Parent;
};