#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>

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

	GLuint indices[] = { 
		0, 1, 3, 
		1, 2, 3   
	};

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(callback, nullptr);

	/// Programm pipeline
	GLuint pipeline;
	glGenProgramPipelines(1, &pipeline);
	glBindProgramPipeline(pipeline);
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
	GLuint frag = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fragmentShaderSource);
	glCheckError();
	GLuint vert = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vertexShaderSource);
	glCheckError();
	GLuint vbo, ibo, vao;
	/// vbo
	glCreateBuffers(1, &vbo);
	glNamedBufferData(vbo, sizeof(vertex_t) * 4, vertices, GL_STATIC_DRAW);
	// ibo
	glCreateBuffers(1, &ibo);
	glNamedBufferData(ibo, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);
	/// vao
	glCreateVertexArrays(1, &vao);
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));

	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, color));

	/// bind vbo, ibo
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(vertex_t));
	glVertexArrayElementBuffer(vao, ibo);

	/// bind vao
	glBindVertexArray(vao);
	glCheckError();
	/// Use shaders
	glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vert);
	glCheckError();
	glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, frag);
	glCheckError();

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
