#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "worldCamera.h"

class Input {

private:

public:
	void processCommonInput(GLFWwindow *window);
	void processAnimationInput(GLFWwindow *window,  double *animationSpeed);
	void processLightInput(GLFWwindow *window,  double *brightness);
	void processCameraInput(GLFWwindow *window, WorldCamera *worldCamera);
};