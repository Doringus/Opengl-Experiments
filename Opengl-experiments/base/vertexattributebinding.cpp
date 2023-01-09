#include "vertexattributebinding.hpp"

#include <cstddef>

#include "vertexarray.hpp"
#include "bufferbase.hpp"

VertexAttributeBinding::VertexAttributeBinding(VertexArray* parent, int bindingIndex) noexcept : m_VertexArray(parent), m_BindingIndex(bindingIndex) { }

void VertexAttributeBinding::enableAttribute(int attributeIndex) {
	glEnableVertexArrayAttrib(m_VertexArray->getHandle(), attributeIndex);
}

void VertexAttributeBinding::bindAttribute(int attributeIndex) {
	glVertexArrayAttribBinding(m_VertexArray->getHandle(), attributeIndex, m_BindingIndex);
}

void VertexAttributeBinding::setFormat(int attributeIndex, size_t size, GLenum type, GLboolean normalized,
	GLuint offset) noexcept {
	glVertexArrayAttribFormat(m_VertexArray->getHandle(), attributeIndex, size, type, normalized, offset);
}

void VertexAttributeBinding::bindElementBuffer(BufferBase& elementBuffer) {
	glVertexArrayElementBuffer(m_VertexArray->getHandle(), elementBuffer.getHandle());
}

void VertexAttributeBinding::bindBuffer(BufferBase& buffer, GLintptr offset, size_t stride) {
	glVertexArrayVertexBuffer(m_VertexArray->getHandle(), m_BindingIndex, buffer.getHandle(), offset, stride);
}
