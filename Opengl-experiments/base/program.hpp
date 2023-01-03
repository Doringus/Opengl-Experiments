#pragma once

#include <cstdint>
#include <string_view>

#include <GL/glew.h>

class Program final {
public:
	Program(std::string_view code, GLenum type) noexcept;

	uint32_t getHandle() const noexcept;
private:
	uint32_t m_Handle{0};
};