#pragma once

#include <concepts>
#include <iterator>

#include <GL/glew.h>

template <class T>
concept StlCompatible = requires(T&& container) {
	{ container.data() } -> std::same_as<typename std::decay_t<T>::value_type*>;
	{ container.size() } -> std::same_as<typename std::decay_t<T>::size_type>;
};

class BufferBase {
public:
	BufferBase() noexcept;
	~BufferBase();

	GLuint getHandle() const noexcept;

	template <StlCompatible T>
	void setData(T&& data, GLenum usage) noexcept {
		glNamedBufferData(m_Handle, data.size() * sizeof(T), data.data(), usage);
	}

protected:
	GLuint m_Handle;
};