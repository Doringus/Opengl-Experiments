#include <GL/glew.h>

static GLenum sizedFormatToBase(GLenum sizedFormat) {
	switch (sizedFormat) {
	case GL_RGBA8: return GL_RGBA;
	case GL_RGBA12: return GL_RGBA;
	case GL_RGBA16: return GL_RGBA;
	case GL_RGBA16F: return GL_RGBA;
	case GL_RGBA32F: return GL_RGBA;
	default: return GL_RGBA;
	}
}