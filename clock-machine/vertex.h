#pragma once

#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

class Vertex
{
public:
	Vertex(glm::vec3 coordinate, glm::vec3 color, glm::vec2 texture);

	//xyz
	glm::vec3 coordinate;
	//3 arguments color
	glm::vec3 color;
	glm::vec2 texture;
};

