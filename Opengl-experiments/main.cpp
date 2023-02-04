#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "base/pipeline.hpp"
#include "base/bufferbase.hpp"
#include "base/vertexarray.hpp"
#include "base/vertexattributebinding.hpp"
#include "base/texture2d.hpp"
#include "base/arraytexture.hpp"
#include "base/bindlesstexture.hpp"

#include "utils/fileloader.hpp"
#include "utils/input.hpp"

#include "scene/scenenode.hpp"
#include "scene/scene.hpp"
#include "scene/camera.hpp"

#include <array>
#include <stb_image.h>

#include "base/textureresource.hpp"

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
	spdlog::info("{0} | {1} | {2}:  ({3})", severity_str, type_str, source_str, message);
}

/// TODO: add frame time
void updateCameraNode(SceneNode* cameraNode, Camera* camera, GLFWwindow* window) {
	constexpr float speed = 0.15f;
	auto position = cameraNode->getTransform().worldPosition;
	auto& cameraFront = camera->getFrontVec();
	auto& cameraUp = camera->getUpVec();

	if (Input::get().isKeyPressed(GLFW_KEY_W)) {
		position += speed * cameraFront;
	}
	if (Input::get().isKeyPressed(GLFW_KEY_S)) {
		position -= speed * cameraFront;
	}
	if (Input::get().isKeyPressed(GLFW_KEY_A)) {
		position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}
	if (Input::get().isKeyPressed(GLFW_KEY_D)) {
		position += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
	}
	cameraNode->setPosition(position);
	/* Rotate camera */
	const auto currentPosition = Input::get().getCurrentFrameMousePosition();
	const auto prevPosition = Input::get().getPreviousFrameMousePosition();
	double offsetX = currentPosition.x - prevPosition.x;
	double offsetY = currentPosition.y - prevPosition.y;
	offsetX *= speed;
	offsetY *= speed;
	cameraNode->getTransform().yaw += offsetX;
	cameraNode->getTransform().pitch -= offsetY;
	if (cameraNode->getTransform().pitch > 89.0f) {
		cameraNode->getTransform().pitch = 89.0f;
	}
	if (cameraNode->getTransform().pitch < -89.0f) {
		cameraNode->getTransform().pitch = -89.0f;
	}
	camera->update();
}

// TODO: make material and light as separate classes
struct directionalLight_t {
	glm::vec3 direction;
	glm::vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;
};

struct material_t {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shines;
};


int main() {
	stbi_set_flip_vertically_on_load(1);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, 640, 480);

	struct vertex_t {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 uv;
		glm::vec3 normal;
	};

	std::array<vertex_t, 4> vertexData = {
		vertex_t { {0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		vertex_t { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		vertex_t { {-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		vertex_t { {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} }
	};

	std::array<GLuint, 6> ind = { 0, 1, 3,
								  1, 2, 3
	};
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(callback, nullptr);

	/// Program pipeline
	Pipeline pipeline;
	
	/// Shaders
	auto vertexShader = readFile(std::filesystem::absolute("res/shaders/basicVertexShader.vert"));
	auto fragmentShader = readFile(std::filesystem::absolute("res/shaders/basicFragmentShader.frag"));
	Program vertexProgram(vertexShader.c_str(), GL_VERTEX_SHADER), fragmentProgram(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
	/// vbo
	BufferBase vertexBuffer;
	vertexBuffer.setData(vertexData, GL_STATIC_DRAW);
	// ibo
	BufferBase elementsBuffer;
	elementsBuffer.setData(ind, GL_STATIC_DRAW);
	/// vao
	VertexArray vertexArray;
	// Position
	vertexArray.binding(0)->enableAttribute(0);
	vertexArray.binding(0)->bindAttribute(0);
	vertexArray.binding(0)->setFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));
	// Color
	vertexArray.binding(0)->enableAttribute(1);
	vertexArray.binding(0)->bindAttribute(1);
	vertexArray.binding(0)->setFormat(1 ,3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, color));
	// Texture
	vertexArray.binding(0)->enableAttribute(2);
	vertexArray.binding(0)->bindAttribute(2);
	vertexArray.binding(0)->setFormat(2, 2, GL_FLOAT, GL_FALSE, offsetof(vertex_t, uv));
	// Normal
	vertexArray.binding(0)->enableAttribute(3);
	vertexArray.binding(0)->bindAttribute(3);
	vertexArray.binding(0)->setFormat(3, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, normal));

	/// bind vbo, ibo
	vertexArray.binding(0)->bindBuffer(vertexBuffer, 0, sizeof(vertex_t));
	vertexArray.binding(0)->bindElementBuffer(elementsBuffer);
	/// bind vao
	vertexArray.bind();

	/// Texture
	TextureResource wall(std::filesystem::absolute("res/textures/wall.png"), 4);
	Texture2d texture(wall, GL_RGBA32F);

	/// Use shaders
	pipeline.useProgramStage(GL_VERTEX_SHADER_BIT, vertexProgram);
	pipeline.useProgramStage(GL_FRAGMENT_SHADER_BIT, fragmentProgram);
	pipeline.bind();

//	fragmentProgram.setUniform("textureSampler", 0);
	/// Test material
	material_t material { .ambient = {1.0f, 0.5f, 0.3f}, .diffuse = {1.0f, 0.5f, 0.3f},
						  .specular = {0.5f, 0.5f, 0.5f}, .emission = {0.3f, 0.3f, 0.3f}, .shines = 32.f };
	/// Test directional light
	directionalLight_t dLight = { .direction = {0.0f, 0.0f, 1.0f}, .color = {1.0f, 0.0f, 0.0f},
		.ambientIntensity = 0.1f, .diffuseIntensity = 0.5f, .specularIntensity = 1.0f };
	// set material params
	fragmentProgram.setUniform("material.ambient", material.ambient);
	fragmentProgram.setUniform("material.diffuse", material.diffuse);
	fragmentProgram.setUniform("material.specular", material.specular);
	fragmentProgram.setUniform("material.emission", material.emission);
	fragmentProgram.setUniform("material.shines", material.shines);
	// set light params
	fragmentProgram.setUniform("directionalLight.direction", dLight.direction);
	fragmentProgram.setUniform("directionalLight.color", dLight.color);
	fragmentProgram.setUniform("directionalLight.ambientIntensity", dLight.ambientIntensity);
	fragmentProgram.setUniform("directionalLight.diffuseIntensity", dLight.diffuseIntensity);
	fragmentProgram.setUniform("directionalLight.specularIntensity", dLight.specularIntensity);

	/// Scene
	Scene scene;
	auto cameraNode = scene.getRootNode().createChild();
	cameraNode->setPosition({0.0, 0.0, -1.0});
	auto camera = std::make_unique<Camera>(glm::perspective(45.0f, 640.f / 480.f,
		0.1f, 500.0f));
	cameraNode->attachGameObject(camera.get());


	texture.bind(0);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/// Input
		glfwPollEvents();
		Input::get().processInput(window);
		/// Update
		updateCameraNode(cameraNode, camera.get(), window);
		/// Draw
		// set matrices to shaders
		// TODO: add model matrix multiplication
		glm::mat4 modelViewMatrix = camera->getViewMatrix() * glm::mat4(1.0);
		glm::mat3 modelViewMatrix3 = glm::mat3(modelViewMatrix);
		glm::mat3 normalMatrix = glm::inverseTranspose(modelViewMatrix3);
		vertexProgram.setUniform(std::string("normalMatrix"), normalMatrix);
		vertexProgram.setUniform(std::string("MVP"), camera->calculateCameraMatrix() * glm::mat4(1.0f));
		vertexProgram.setUniform(std::string("modelViewMatrix"), modelViewMatrix);
//		fragmentProgram.setUniform(std::string("cameraPosition"), cameraNode->getTransform().worldPosition);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(window);
	}

	return 0;
}
