#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/camera.h>
#include "shprogram.h"
#include "mesh.h"
#include "cube.h"
#include "floor.h"
#include "cylinder.h"
#include "cover.h"
#include "cuboid.h"
#include "trans.h"

using namespace std;

double animationSpeed = 1;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
GLuint LoadMipmapTexture(GLuint texId, const char *fname);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const GLuint WIDTH = 800, HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{

	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "zegar", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

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

		// Build, compile and link shader program
		ShaderProgram theProgram("clock_machine.vert", "clock_machine.frag");
		ShaderProgram skyboxShader("skybox.vert", "skybox.frag");

		// Create mesh
		Mesh *cube = new Cube();
		cube->init();
		cube->loadTexture("wood.png");

		Mesh *skybox = new Cube();
		skybox->init();

		Mesh *cylinder = new Cylinder(12, 0.45, 0.55, 0);
		cylinder->init();
		cylinder->loadTexture("white_wood.png");

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

		vector<std::string> faces{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg"};
		unsigned int cubemapTexture = loadCubemap(faces);

		// shader configuration
		// --------------------

		skyboxShader.use();
		skyboxShader.setInt("skybox", 0);
		Mesh *plug = new Cylinder(36, 0.08, 0.07, 1);
		plug->init();

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// per-frame time logic
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// input
			// -----
			processInput(window);

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			theProgram.Use();

			// pass projection matrix to shader (note that in this case it could change every frame)
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			theProgram.setMat4("projection", projection);

			// camera/view transformation
			glm::mat4 view = camera.GetViewMatrix();
			theProgram.setMat4("view", view);

			// Pass transformation matrices to the shader
			theProgram.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
			theProgram.setMat4("view", view);

			// Ustawienie i rysowanie obudowy
			Trans tranformation;
			glm::mat4 model = glm::mat4(1.0f);

			// Ustawiamy obiekt
			tranformation.translate(model, 0, 0.5, -0.5);
			// Obracamy
			tranformation.rotate(model, 1, 0, 0, 90);
			// Skalujemy
			tranformation.scale(model, 1, 1, 1);

			theProgram.setMat4("model", model);
			cover->draw();

			//ustawienie i rysowanie cyferblatu
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0, 0.5, -0.5);
			tranformation.rotate(model, 1, 0, 0, 90);
			tranformation.scale(model, 1, 1, 1);

			theProgram.setMat4("model", model);
			cylinder->draw();

			//ustawienie i rysowanie wskazowki 1

			model = glm::mat4(1.0f);
			static GLfloat rot_angle = 0.0f;

			rot_angle -= 0.12 * animationSpeed;
			if (rot_angle <= -360)
				rot_angle = 0.0f;

			tranformation.translate(model, 0, 0.5, -0.25);
			tranformation.rotate(model, 0, 0, 1, rot_angle);
			tranformation.scale(model, 0.2, 0.8, 0.8);

			theProgram.setMat4("model", model);
			pointer->draw();

			//ustawienie i rysowanie wskazowki 2
			model = glm::mat4(1.0f);
			static GLfloat rot_angle2 = 0.0f;

			rot_angle2 -= 0.01 * animationSpeed;

			if (rot_angle2 <= -360)
				rot_angle2 = 0.0f;

			tranformation.translate(model, 0, 0.5, -0.28);
			tranformation.rotate(model, 0, 0, 1, rot_angle2);
			tranformation.scale(model, 0.4, 0.6, 0.8);

			theProgram.setMat4("model", model);
			pointer->draw();

			//ustawienie i rysowanie srodka cyferblatu
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0, 0.5, -0.3);
			tranformation.rotate(model, 1, 0, 0, 90);
			tranformation.scale(model, 1, 1, 1);

			theProgram.setMat4("model", model);
			plug->draw();

			//ustawienie i rysowanie dzwonka
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0.25, 1, -0.5);
			tranformation.rotate(model, 0, 0, 1, -30);
			tranformation.scale(model, 1, 1, 1);

			theProgram.setMat4("model", model);
			bell->draw();

			//ustawienie i rysowanie dzwonka 2
			model = glm::mat4(1.0f);

			tranformation.translate(model, -0.25, 1, -0.5);
			tranformation.rotate(model, 0, 0, 1, 30);
			tranformation.scale(model, 1, 1, 1);

			theProgram.setMat4("model", model);
			bell->draw();

			//ustawienie i rysowanie szafki
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0, -0.5, -0.5);
			theProgram.setMat4("model", model);
			cube->draw();

			// Ustawienie i rysowanie podłogi
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0, -1.5, -1.5);
			tranformation.scale(model, 100, 1, 100);
			theProgram.setMat4("model", model);
			floor->draw();

			// Ustawienie i rysowanie pod�ogi
			model = glm::mat4(1.0f);

			tranformation.translate(model, 0, -1.5, -1.5);
			tranformation.scale(model, 100, 1, 100);
			theProgram.setMat4("model", model);
			floor->draw();

			// draw skybox as last
			glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
			skyboxShader.use();
			view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
			skyboxShader.setMat4("view", view);
			skyboxShader.setMat4("projection", projection);

			// skybox cube
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			skybox->draw();
			glDepthFunc(GL_LESS); // set depth function back to default

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

GLuint LoadMipmapTexture(GLuint texId, const char *fname)
{
	int width, height;
	unsigned char *image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && animationSpeed < 5)
		animationSpeed += 0.02;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && animationSpeed >= 0.02)
		animationSpeed -= 0.02;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
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
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: ";
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
