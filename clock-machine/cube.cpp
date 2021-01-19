#include "cube.h"

using namespace glm;

void Cube::setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices)
{
	vertices.push_back(Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f)));
	vertices.push_back(Vertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 1.0f)));
	vertices.push_back(Vertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f)));
	vertices.push_back(Vertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f)));

	vertices.push_back(Vertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 1.0f)));
	vertices.push_back(Vertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(1.0f, 0.0f)));
	vertices.push_back(Vertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 0.0f)));
	vertices.push_back(Vertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.5f, 0.5f, 0.5f), vec2(0.0f, 1.0f)));

	indices = {
		0,1,2,
		0,2,3,
		1,6,2,
		1,5,6,
		4,5,1,
		4,1,0,
		4,0,3,
		4,3,7,
		3,2,6,
		3,6,7,
		7,6,5,
		7,5,4
	};
}