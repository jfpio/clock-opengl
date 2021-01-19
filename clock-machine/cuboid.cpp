#include "cuboid.h"
using namespace glm;

void Cuboid::setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
	glm::vec3 color = glm::vec3(0.01f, 0.02f, 0.01f);

	vertices.push_back(Vertex(vec3(0.0f, 0.0f, 0.0f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.05f, 0.0f, 0.0f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.05f, 0.5f, 0.0f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.0f, 0.5f, 0.0f), color, vec2()));

	vertices.push_back(Vertex(vec3(0.0f, 0.0f, -0.02f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.05f, 0.0f, -0.02f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.05f, 0.5f, -0.02f), color, vec2()));
	vertices.push_back(Vertex(vec3(0.0f, 0.5f, -0.02f), color, vec2()));


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
