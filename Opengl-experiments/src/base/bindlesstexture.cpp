#include "bindlesstexture.hpp"

BindlessTexture::BindlessTexture(const TextureResource& resource, GLenum internalFormat)
			: Texture2d(resource, internalFormat), m_TextureHandle(*this) {
	
}

const TextureHandle& BindlessTexture::getBindlessHandle() const noexcept {
	return m_TextureHandle;
}
