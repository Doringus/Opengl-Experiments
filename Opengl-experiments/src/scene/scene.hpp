#pragma once

#include "scenenode.hpp"

class Scene final {
public:
	Scene() noexcept;

	SceneNode& getRootNode() noexcept;
	const SceneNode& getRootNode() const noexcept;

private:
	SceneNode m_Root;
};