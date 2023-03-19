#include "arraytexture.hpp"

#include "textureformat.hpp"

ArrayTexture::ArrayTexture(const std::vector<TextureResource>& images, int width, int height, GLenum internalFormat) {
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_Handle);
	glTextureStorage3D(m_Handle, 1, internalFormat, width, height, images.size());
	setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	constexpr GLint xOffset = 0, yOffset = 0, zOffset = 0;
	for (int i = 0; i < images.size(); ++i) {
		glTextureSubImage3D(m_Handle, 0, xOffset, yOffset, i, images.at(i).getWidth(), images.at(i).getHeight(), 1, sizedFormatToBase(internalFormat), GL_UNSIGNED_BYTE,
			reinterpret_cast<const unsigned char*>(images.at(i).getImageData().data()));
	}

}
