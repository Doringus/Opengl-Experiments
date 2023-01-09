#include "bufferbase.hpp"

BufferBase::BufferBase() noexcept {
	glCreateBuffers(1, &m_Handle);
}

BufferBase::~BufferBase() {
	glDeleteBuffers(1, &m_Handle);
}

GLuint BufferBase::getHandle() const noexcept {
	return m_Handle;
}
