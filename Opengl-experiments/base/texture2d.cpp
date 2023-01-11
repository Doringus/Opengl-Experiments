#include "texture2d.hpp"

#include "textureresource.hpp"

GLenum sizedFormatToBase(GLenum sizedFormat) {
	switch (sizedFormat) {
		case GL_RGBA8: return GL_RGBA;
		case GL_RGBA12: return GL_RGBA;
		case GL_RGBA16: return GL_RGBA;
		case GL_RGBA16F: return GL_RGBA;
		case GL_RGBA32F: return GL_RGBA;
		default: return GL_RGBA;
	}
}

Texture2d::Texture2d(const TextureResource& resource, GLenum internalFormat) {
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
	setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureStorage2D(m_Handle, 1, internalFormat, resource.getWidth(), resource.getHeight());
	glTextureSubImage2D(m_Handle, 0, 0, 0, resource.getWidth(), resource.getHeight(), 
		sizedFormatToBase(internalFormat), GL_UNSIGNED_BYTE, reinterpret_cast<const unsigned char*>(resource.getImageData().data()));
}
