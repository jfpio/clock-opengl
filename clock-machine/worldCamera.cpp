#include "worldCamera.h"

WorldCamera::WorldCamera(const GLuint width, const GLuint height) {
	float lastX = width / 2.0f;
	float lastY = height / 2.0f;
}

float WorldCamera::getLastX() {
	return lastX;
};

float WorldCamera::getLastY() {
	return lastY;
};

float WorldCamera::getDeltaTime() {
	return deltaTime;
};

bool WorldCamera::getIsFirstMove() {
	return isFirstMove;
}

void WorldCamera::setLastX(float value) {
	lastX = value;
};

void WorldCamera::setLastY(float value) {
	lastY = value;
};

void WorldCamera::setDeltaTime(float value) {
	deltaTime = value - lastFrame;
};

void WorldCamera::setLastFrame(float value) {
	lastFrame = value;
};

void WorldCamera::setIsFirstMove(bool value) {
	isFirstMove = value;
};