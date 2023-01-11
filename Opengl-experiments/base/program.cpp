#include "program.hpp"

#include <array>
#include <string>
#include <spdlog/spdlog.h>

Program::Program(std::string_view code, GLenum type) noexcept {
	const auto codePtr = code.data();
	m_Handle = glCreateShaderProgramv(type, 1, &codePtr);
	/// Check errors
	GLint isLinked = 0;
	glGetProgramiv(m_Handle, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &maxLength);

		std::string errorLog;
		errorLog.resize(maxLength);

		glGetProgramInfoLog(m_Handle, maxLength, &maxLength, &errorLog[0]);
		spdlog::error("Shader compiler error: {}", errorLog);
	}
	/// Get uniforms
	GLint uniformsCount;
	glGetProgramInterfaceiv(m_Handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &uniformsCount);
	std::array<GLenum, 2> uniformParamTypes = { GL_NAME_LENGTH, GL_LOCATION };
	std::vector<GLchar> uniformNameCstr;
	for (int i = 0; i < uniformsCount; ++i) {
		std::array<GLint, 2> uniformParams;
		glGetProgramResourceiv(m_Handle, GL_UNIFORM, i, uniformParamTypes.size(), uniformParamTypes.data(),
			uniformParams.size(), nullptr, uniformParams.data());
		uniformNameCstr.resize(uniformParams[0]);
		glGetProgramResourceName(m_Handle, GL_UNIFORM, i, uniformNameCstr.size(), nullptr, uniformNameCstr.data());
		std::string name((char*)&uniformNameCstr[0], uniformNameCstr.size() - 1);
		m_UniformLocations[name] = uniformParams[1];
	}
 }

uint32_t Program::getHandle() const noexcept {
	return m_Handle;
}
