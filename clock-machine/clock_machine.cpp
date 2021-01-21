#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shprogram.h"
#include "mesh.h"
#include "cube.h"
#include "floor.h"
#include "cylinder.h"
#include "cover.h"
#include "cuboid.h"
#include "trans.h"
#include "environment.h"
#include "input.h"
#include "worldCamera.h"
#include "drawer.h"

using namespace std;

// settings
double animationSpeed = 1;
static GLfloat minutePointerAngel = 0;
static GLfloat hourPointerAngel = 0;
double brightness = 0.8;
const GLuint WIDTH = 800, HEIGHT = 600;

Input *input = new Input();
WorldCamera *worldCamera = new WorldCamera(WIDTH, HEIGHT);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "zegar", nullptr, nullptr);
		if (window == nullptr) 	throw exception("GLFW window not created");

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) 	throw exception("GLEW Initialization failed");

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

		Drawer *drawer = new Drawer();
		
		Environment *environment = new Environment();

		Mesh *cube = new Cube();
		cube->init();
		cube->loadTexture("wood.png");

		Mesh *skybox = new Cube();
		skybox->init();

		Mesh *frontOfClock = new Cylinder(12, 0.45, 0.55, 0);
		frontOfClock->init();
		frontOfClock->loadTexture("white_wood.png");

		Mesh *cover = new Cover(24, 0.5, 0.6, 0.05);
		cover->init();
		cover->loadTexture("clock.png");

		Mesh *pointer = new Cuboid();
		pointer->init();

		Mesh *bell = new Cylinder(36, 0.2, 0.15, 0.5);
		bell->init();
		bell->loadTexture("silver_material.png");

		Mesh *floor = new Floor();
		floor->init();
		floor->loadTexture("sand.png");

		Mesh *plug = new Cylinder(36, 0.08, 0.2, 1);
		plug->init();

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// per-frame time logic
			float currentFrame = glfwGetTime();
			worldCamera->setDeltaTime(currentFrame);
			worldCamera->setLastFrame(currentFrame);

			input->processCommonInput(window);
			input->processAnimationInput(window, &animationSpeed);
			input->processLightInput(window, &brightness);
			input->processCameraInput(window, worldCamera);

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//settings
			glm::mat4 projection = glm::perspective(glm::radians(worldCamera->camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = worldCamera->camera.GetViewMatrix();
			
			drawer->useCommonShader(view, projection, brightness);
			
			drawer->drawCover(cover);
			drawer->drawFrontOfClock(frontOfClock);
			drawer->drawMinutePointer(pointer, &animationSpeed, &minutePointerAngel);
			drawer->drawHourPointer(pointer, &animationSpeed, &hourPointerAngel);
			drawer->drawPlug(plug);
			drawer->drawFirstBell(bell);
			drawer->drawSecondBell(bell);
			drawer->drawCube(cube);
			drawer->drawFloor(floor);

			view = glm::mat4(glm::mat3(worldCamera->camera.GetViewMatrix())); // remove translation from the view matrix

			drawer->useSkyboxShader(view, projection);

			drawer->drawSkybox(skybox, environment);

			// Swap the screen buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos){
	if (worldCamera->getIsFirstMove()) {
		worldCamera->setLastX(xpos);
		worldCamera->setLastY(ypos);
		worldCamera->setIsFirstMove(false);
	}

	float lastX = worldCamera->getLastX();
	float lastY = worldCamera->getLastY();

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	worldCamera->setLastX(xpos);
	worldCamera->setLastY(ypos);

	worldCamera->camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	worldCamera->camera.ProcessMouseScroll(yoffset);
}
