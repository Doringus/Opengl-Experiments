#include "program.hpp"

Program::Program(std::string_view code, GLenum type) noexcept {
	const auto codePtr = code.data();
	m_Handle = glCreateShaderProgramv(type, 1, &codePtr);
}

uint32_t Program::getHandle() const noexcept {
	return m_Handle;
}
