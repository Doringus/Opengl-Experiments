#include "vertexarray.hpp"

#include "bufferbase.hpp"
#include "vertexattributebinding.hpp"

VertexArray::VertexArray() noexcept {
	glCreateVertexArrays(1, &m_Handle);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_Handle);
}

void VertexArray::bind() {
	glBindVertexArray(m_Handle);
}

VertexAttributeBinding* VertexArray::binding(GLuint bindingIndex) noexcept {
	if(m_Bindings.contains(bindingIndex)) {
		return m_Bindings[bindingIndex].get();
	}

	const auto it = m_Bindings.emplace(bindingIndex, std::make_unique<VertexAttributeBinding>(this, bindingIndex));
	return it.first->second.get();
}

GLuint VertexArray::getHandle() const noexcept {
	return m_Handle;
}
