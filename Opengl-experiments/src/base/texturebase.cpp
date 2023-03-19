#include "texturebase.hpp"

TextureBase::~TextureBase() {
	glDeleteTextures(1, &m_Handle);
}

void TextureBase::bind(GLuint slot) {
	glBindTextureUnit(slot, m_Handle);
}

GLuint TextureBase::getHandle() const noexcept {
	return m_Handle;
}
