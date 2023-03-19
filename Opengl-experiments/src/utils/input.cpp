#include "input.hpp"

void Input::processInput(GLFWwindow* activeWindow) noexcept {
	for(int i = GLFW_KEY_A; i <= GLFW_KEY_Z; ++i) {
		m_Keys[i] = glfwGetKey(activeWindow, i);
	}
	m_PreviousFrameMousePosition = m_CurrentFrameMousePosition;
	glfwGetCursorPos(activeWindow, &m_CurrentFrameMousePosition.x, &m_CurrentFrameMousePosition.y);
}

bool Input::isKeyPressed(int keyCode) const noexcept {
	return m_Keys.at(keyCode);
}

mousePosition_t Input::getCurrentFrameMousePosition() const noexcept {
	return m_CurrentFrameMousePosition;
}

mousePosition_t Input::getPreviousFrameMousePosition() const noexcept {
	return m_PreviousFrameMousePosition;
}
