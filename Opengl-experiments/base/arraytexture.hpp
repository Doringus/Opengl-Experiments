#pragma once

#include <vector>

#include "texturebase.hpp"
#include "textureresource.hpp"

class ArrayTexture : public TextureBase {
public:
	ArrayTexture(const std::vector<TextureResource>& images, int width, int height, GLenum internalFormat);

};