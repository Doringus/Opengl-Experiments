#pragma once

#include "texturebase.hpp"

class TextureResource;

static GLenum sizedFormatToBase(GLenum sizedFormat);

class Texture2d : public TextureBase {
public:
	Texture2d(const TextureResource& resource, GLenum internalFormat);
};