#pragma once

#include <GL/glew.h>

class TextureBase;

class TextureHandle final {
public:
	explicit TextureHandle(GLuint64 handle) noexcept;
	explicit TextureHandle(const TextureBase& texture) noexcept;

	GLuint64 getHandle() const noexcept;

	void makeResident() const noexcept;
	void makeNonResident() const noexcept;

private:
	GLuint64 m_Handle;
};