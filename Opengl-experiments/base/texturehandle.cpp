#include "texturehandle.hpp"

#include "texturebase.hpp"

TextureHandle::TextureHandle(GLuint64 handle) noexcept {
	m_Handle = handle;
}

TextureHandle::TextureHandle(const TextureBase& texture) noexcept {
	m_Handle = glGetTextureHandleARB(texture.getHandle());
}

GLuint64 TextureHandle::getHandle() const noexcept {
	return m_Handle;
}

void TextureHandle::makeResident() const noexcept {
	glMakeTextureHandleResidentARB(m_Handle);
}

void TextureHandle::makeNonResident() const noexcept {
	glMakeTextureHandleNonResidentARB(m_Handle);
}
