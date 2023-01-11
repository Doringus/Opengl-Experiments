#pragma once

#include <GL/glew.h>

class TextureHandle final {
public:
	explicit TextureHandle(GLuint64 handle) noexcept;
	// explicit TextureHandle(const Texture& texure) noexcept;

	GLuint64 getHandle() const noexcept;

	void makeResident() noexcept;
	void makeNonResident() noexcept;

private:
	GLuint64 m_Handle;
};