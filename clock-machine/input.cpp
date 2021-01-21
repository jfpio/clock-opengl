#include "input.h"

void Input::processCommonInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Input::processAnimationInput(GLFWwindow *window, double *animationSpeed) {
	double animationSpeedValue = *animationSpeed;

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && animationSpeedValue < 5)
		animationSpeedValue += 0.02;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && animationSpeedValue >= 0.02)
		animationSpeedValue -= 0.02;

	*animationSpeed = animationSpeedValue;
}

void Input::processCameraInput(GLFWwindow *window, WorldCamera *worldCamera){
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		worldCamera->camera.ProcessKeyboard(FORWARD, worldCamera->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		worldCamera->camera.ProcessKeyboard(BACKWARD, worldCamera->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		worldCamera->camera.ProcessKeyboard(LEFT, worldCamera->deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		worldCamera->camera.ProcessKeyboard(RIGHT, worldCamera->deltaTime);
};