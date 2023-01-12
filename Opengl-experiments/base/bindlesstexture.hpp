#pragma once

#include "texture2d.hpp"
#include "texturehandle.hpp"

class BindlessTexture : public Texture2d {
public:
	BindlessTexture(const TextureResource& resource, GLenum internalFormat);

	const TextureHandle& getBindlessHandle() const noexcept;

private:
	TextureHandle m_TextureHandle;
};