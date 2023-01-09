﻿#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>

#include "base/pipeline.hpp"
#include "base/bufferbase.hpp"
#include "base/vertexarray.hpp"
#include "base/vertexattributebinding.hpp"

#include <array>

static GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		spdlog::error("{0} | {1} ({2})", error, file, line);
	}
	return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto source_str = [source]() -> std::string {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:  return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		default: return "UNKNOWN";
		}
	}();

	auto type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER:  return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		default: return "UNKNOWN";
		}
	}();

	auto severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		default: return "UNKNOWN";
		}
	}();
	spdlog::info("{0} | {1} ({2})", severity_str, type_str, message);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Experimetns", nullptr, nullptr);
	if (!window) {
		spdlog::critical("Cannot create GLFW window");
	}
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK) {
		spdlog::critical("Cannot init glew");
	}
	glewExperimental = GL_TRUE;
	glViewport(0, 0, 640, 480);

	struct vertex_t {
		glm::vec3 position;
		glm::vec3 color;
	};

	vertex_t vertices[] = {
		vertex_t { {0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} },
		vertex_t { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} },
		vertex_t { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		vertex_t { {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} }
	};
	std::array<vertex_t, 4> vertexData = {
		vertex_t { {0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} },
		vertex_t { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} },
		vertex_t { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		vertex_t { {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} }
	};

	GLuint indices[] = { 
		0, 1, 3, 
		1, 2, 3   
	};
	std::array<GLuint, 6> ind = { 0, 1, 3,
								  1, 2, 3 };
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(callback, nullptr);

	/// Programm pipeline
	Pipeline pipeline;
	/// Shaders code

	const GLchar* vertexShaderSource = "#version 450 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"layout (location = 0) out vec3 outColor;\n"
		"out gl_PerVertex\n"
		"{\n"
        "vec4 gl_Position;\n"
        "float gl_PointSize;\n"
        "float gl_ClipDistance[];\n"
		"};\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0);\n"
		"outColor = color;\n"
		"}\0";

	const GLchar* fragmentShaderSource = "#version 450 core\n"
		"layout (location = 0) in vec3 inColor;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(inColor, 1.0f);\n"
		"}\n\0";


	/// Shaders
	Program vertexProgram(vertexShaderSource, GL_VERTEX_SHADER), fragmentProgram(fragmentShaderSource, GL_FRAGMENT_SHADER);

	/// vbo
	BufferBase vertexBuffer;
	vertexBuffer.setData(vertexData, GL_STATIC_DRAW);
	// ibo
	BufferBase elementsBuffer;
	elementsBuffer.setData(ind, GL_STATIC_DRAW);
	/// vao
	VertexArray vertexArray;
	vertexArray.binding(0)->enableAttribute(0);
	vertexArray.binding(0)->bindAttribute(0);
	vertexArray.binding(0)->setFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));

	vertexArray.binding(0)->enableAttribute(1);
	vertexArray.binding(0)->bindAttribute(1);
	vertexArray.binding(0)->setFormat(1 ,3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, color));

	/// bind vbo, ibo
	vertexArray.binding(0)->bindBuffer(vertexBuffer, 0, sizeof(vertex_t));
	vertexArray.binding(0)->bindElementBuffer(elementsBuffer);
	/// bind vao
	vertexArray.bind();
	glCheckError();
	/// Use shaders
	pipeline.useProgramStage(GL_VERTEX_SHADER_BIT, vertexProgram);
	pipeline.useProgramStage(GL_FRAGMENT_SHADER_BIT, fragmentProgram);
	pipeline.bind();

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCheckError();
		glfwPollEvents();
		/// Draw
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glCheckError();
		glfwSwapBuffers(window);
	}

	return 0;
}
