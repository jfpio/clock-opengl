#include "configuration.h"

Configuration::Configuration() {

}

void Configuration::init(GLFWwindow *window) {
	if (window == nullptr)
		throw std::exception("GLFW window not created");
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::exception("GLEW Initialization failed");

	glEnable(GL_DEPTH_TEST);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, WIDTH, HEIGHT);

	// Let's check what are maximum parameters counts
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
	glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
	cout << "Max texture coords allowed: " << nrAttributes << std::endl;
};