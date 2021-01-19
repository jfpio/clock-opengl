#include "cover.h"
void Cover::setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
	//generate vertices of top and bottom circles
	genVertices(vertices);

	genIndices(indices);
}

Cover::Cover(int _slices, float _radius, float _height, float _thickness)
{
	slices = _slices;
	radius = _radius;
	height = _height;
	thickness = _thickness;
}

void Cover::genVertices(std::vector<Vertex> &vertices) {
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	//glm::vec3 color2 = glm::vec3(0.0f, 0.0f, 0.1f);
	glm::vec3 centerTop = glm::vec3(0.0f, height / 2, 0.0f);
	glm::vec3 centerBot = glm::vec3(0.0f, -height / 2, 0.0f);

	GLfloat innerRadius = radius - thickness;

	//center of bottom circle
	vertices.push_back(Vertex(centerBot, color, glm::vec2()));
	// bottom in ring
	for (float i = 0.0f; i < 360.0f; i += (360.0f / slices)) {
		vertices.push_back(Vertex(glm::vec3(innerRadius  * cosf(i * M_PI / 180.0), - height/2.0, innerRadius * sinf(i*M_PI / 180.0)), color, glm::vec2()));
	}
	//bottom out ring
	for (float i = 0.0f; i < 360.0f; i += (360.0f / slices)) {
		vertices.push_back(Vertex(glm::vec3(radius * cosf(i * M_PI / 180.0), -height / 2.0, radius * sinf(i*M_PI / 180.0)), color, glm::vec2()));
	}
	//top in ring
	for (float i = 0.0f; i < 360.0f; i += (360.0f / slices)) {
		vertices.push_back(Vertex(glm::vec3(innerRadius  * cosf(i * M_PI / 180.0), height / 2.0, innerRadius * sinf(i*M_PI / 180.0)), color, glm::vec2()));
	}
	//top out ring
	for (float i = 0.0f; i < 360.0f; i += (360.0f / slices)) {
		vertices.push_back(Vertex(glm::vec3(radius * cosf(i * M_PI / 180.0), height / 2.0, radius * sinf(i*M_PI / 180.0)), color, glm::vec2()));
	}
}


void Cover::genIndices(std::vector<GLuint> &indices) {
	//bottom circle
	for (unsigned int i = 0; i < slices; i++) {
		indices.push_back(0);
		indices.push_back(slices + i + 1);
		if (i + 1 == slices)
			indices.push_back(slices + 1);
		else
			indices.push_back(slices + i + 2);
	}

	//inner side
	for (unsigned int i = 1; i < slices; i++) {
		indices.push_back(i);
		indices.push_back(i + 2*slices );
		indices.push_back(i + 2*slices + 1);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2*slices + 1);
	}

	indices.push_back(slices);
	indices.push_back(3 * slices);
	indices.push_back(2 * slices + 1);

	indices.push_back(slices);
	indices.push_back(1);
	indices.push_back(2 * slices + 1);

	//out side
	for (unsigned int i = 1; i < slices; i++) {
		indices.push_back(i + slices);
		indices.push_back(i + 3 * slices);
		indices.push_back(i + 3 * slices + 1);

		indices.push_back(i + slices);
		indices.push_back(i + slices + 1);
		indices.push_back(i + 3 * slices + 1);
	}

	indices.push_back(2 * slices);
	indices.push_back(4 * slices);
	indices.push_back(3 * slices + 1);

	indices.push_back(slices + 1);
	indices.push_back(2 * slices);
	indices.push_back(3* slices + 1);


	//ring
	for (unsigned int i = 1; i < slices; i++) {

		indices.push_back(2 * slices + i);
		indices.push_back(2 * slices + i + 1);
		indices.push_back(3 * slices + i);

		indices.push_back(2 * slices + i + 1);
		indices.push_back(3 * slices + i + 1);
		indices.push_back(3 * slices + i);
	}

	indices.push_back(3 * slices);
	indices.push_back(4 * slices);
	indices.push_back(2 * slices + 1);

	indices.push_back(2 * slices + 1);
	indices.push_back(3 * slices + 1);
	indices.push_back(4 * slices);
}