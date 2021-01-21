#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <learnopengl/camera.h>

class Input {

private:

public:
	void processCommonInput(GLFWwindow *window);
	void processAnimationInput(GLFWwindow *window,  double *animationSpeed);
	void processCameraInput(GLFWwindow *window, Camera *camera, float deltaTime);
};