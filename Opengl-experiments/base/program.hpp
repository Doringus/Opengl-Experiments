#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program final {
public:
	Program(std::string_view code, GLenum type) noexcept;

	uint32_t getHandle() const noexcept;


	template <typename T>
	void setUniform(const std::string& name, const T& uniform);

private:
	uint32_t m_Handle{0};
	std::unordered_map<std::string, GLint> m_UniformLocations;
};

template <>
inline void Program::setUniform<glm::mat4>(const std::string& name, const glm::mat4& uniform) {
	glProgramUniformMatrix4fv(m_Handle, m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(uniform));
}

template <>
inline void Program::setUniform<glm::mat3>(const std::string& name, const glm::mat3& uniform) {
	glProgramUniformMatrix3fv(m_Handle, m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(uniform));
}


template <>
inline void Program::setUniform<GLuint64>(const std::string& name, const GLuint64& uniform) {
	glProgramUniformHandleui64ARB(m_Handle, m_UniformLocations[name], uniform);
}

template <>
inline void Program::setUniform<glm::vec3>(const std::string& name, const glm::vec3& uniform) {
	glProgramUniform3fv(m_Handle, m_UniformLocations[name], 1, glm::value_ptr(uniform));
}

template <>
inline void Program::setUniform<GLint>(const std::string& name, const GLint& uniform) {
	glProgramUniform1i(m_Handle, m_UniformLocations[name], uniform);
}
