#pragma once

#include <GL/glew.h>

class TextureBase {
public:
	virtual ~TextureBase();
	
	virtual void bind(GLuint slot);
	GLuint getHandle() const noexcept;

	template <typename T>
	void setParameter(GLenum name, T parameter);
protected:
	GLuint m_Handle;
};

template <>
inline void TextureBase::setParameter<GLint>(GLenum name, GLint parameter) {
	glTextureParameteri(m_Handle, name, parameter);
}

template <>
inline void TextureBase::setParameter<GLfloat>(GLenum name, GLfloat parameter) {
	glTextureParameterf(m_Handle, name, parameter);
}
