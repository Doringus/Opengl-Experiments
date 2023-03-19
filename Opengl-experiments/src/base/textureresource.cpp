#include "textureresource.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureResource::TextureResource(const std::filesystem::path& path, int channels) : m_Channels(channels) {
	unsigned char* data = stbi_load(path.string().c_str(), &m_Width, &m_Height, &m_BPP, channels);
	m_Data.reserve(m_Width * m_Height * channels);
	for (size_t i = 0; i < m_Width * m_Height * channels; ++i) {
		m_Data.push_back(std::byte{ data[i] });
	}
	stbi_image_free(data);
}

int TextureResource::getBpp() const noexcept {
	return m_BPP;
}

int TextureResource::getWidth() const noexcept {
	return m_Width;
}

int TextureResource::getHeight() const noexcept {
	return m_Height;
}

std::vector<std::byte> const& TextureResource::getImageData() const noexcept {
	return m_Data;
}
