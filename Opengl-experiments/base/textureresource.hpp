#pragma once

#include <vector>
#include <filesystem>


class TextureResource final {
public:
	TextureResource(const std::filesystem::path& path, int channels);

	int getBpp() const noexcept;
	int getWidth() const noexcept;
	int getHeight() const noexcept;

	std::vector<std::byte> const& getImageData() const noexcept;

private:
	int m_Width, m_Height, m_BPP, m_Channels;
	std::vector<std::byte> m_Data;
};