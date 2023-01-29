#pragma once

#include <GLFW/glfw3.h>

#include <unordered_map>

#include "singleton.hpp"

struct mousePosition_t {
	double x = 0;
	double y = 0;
};

class Input final : public Singleton<Input> {
public:
	void processInput(GLFWwindow* activeWindow) noexcept;
	bool isKeyPressed(int keyCode) const noexcept;

	mousePosition_t getCurrentFrameMousePosition() const noexcept;
	mousePosition_t getPreviousFrameMousePosition() const noexcept;
private:
	std::unordered_map<int, bool> m_Keys;
	mousePosition_t m_CurrentFrameMousePosition, m_PreviousFrameMousePosition;
};