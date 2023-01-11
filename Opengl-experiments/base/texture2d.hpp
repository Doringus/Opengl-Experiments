#pragma once

#include "texturebase.hpp"

class TextureResource;

class Texture2d : public TextureBase {
public:
	Texture2d(const TextureResource& resource, GLenum internalFormat);
};