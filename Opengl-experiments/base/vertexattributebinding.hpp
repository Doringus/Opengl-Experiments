#pragma once

#include <GL/glew.h>


class VertexArray;
class BufferBase;

class VertexAttributeBinding {
public:
	VertexAttributeBinding(VertexArray* parent, int bindingIndex) noexcept;

	void enableAttribute(int attributeIndex);
	void bindAttribute(int attributeIndex);
	void setFormat(int attributeIndex, size_t size, GLenum type, GLboolean normalized, GLuint offset) noexcept;

	void bindElementBuffer(BufferBase& elementBuffer);
	void bindBuffer(BufferBase& buffer, GLintptr offset, size_t stride);

private:
	int m_BindingIndex;
	VertexArray* m_VertexArray;
};