#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Trans
{
public:
	void translate(glm::mat4 &model, float x, float y, float z);
	void scale(glm::mat4 &model, float x, float y, float z);
	void rotate(glm::mat4 &model, float x, float y, float z, float angle);
	Trans();
private:
	glm::mat4 model;
};

