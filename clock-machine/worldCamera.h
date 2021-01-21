#pragma once

#include <learnopengl/camera.h>
#include <glm/glm.hpp>

class WorldCamera
{
	float lastX;
	float lastY;
	bool isFirstMove = true;

public:
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	WorldCamera(const GLuint width, const GLuint height);
	float getLastX();
	float getLastY();
	float getDeltaTime();
	bool getIsFirstMove();
	void setLastX(float value);
	void setLastY(float value);
	void setDeltaTime(float value);
	void setLastFrame(float value);
	void setIsFirstMove(bool value);
};