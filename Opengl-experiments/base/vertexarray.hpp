#pragma once

#include <GL/glew.h>

#include <unordered_map>
#include <memory>

class BufferBase;
class VertexAttributeBinding;

class VertexArray final {
public:
	VertexArray() noexcept;
	~VertexArray();

	void bind();
	VertexAttributeBinding* binding(GLuint bindingIndex) noexcept;

	GLuint getHandle() const noexcept;

private:
	GLuint m_Handle;
	std::unordered_map<GLuint, std::unique_ptr<VertexAttributeBinding>> m_Bindings;
};