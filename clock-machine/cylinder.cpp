#include "cylinder.h"

void Cylinder::setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) {
	//generate vertices of top and bottom circles
	genVertices(vertices, false);
	genVertices(vertices, true);
	
	genIndices(indices);
}

Cylinder::Cylinder(int _slices, float _radius, float _height, int _color)
{
	slices = _slices;
	radius = _radius;
	height = _height;
	col = _color;
}


void Cylinder::genVertices(std::vector<Vertex> &vertices, bool isTop) {
	glm::vec3 color = glm::vec3(0.95f, 0.0f, 0.0f);
	if (col == 0)
		color = glm::vec3(0.95f, 0.95f, 0.95f);
	else 
		color = glm::vec3(0.8f, 0.8f, 0.8f);

	glm::vec3 center;
	double y;

	if (isTop) {
		glm::vec3 center = glm::vec3(0.0, height/2.0, 0.0);
		y = height/2.0;
	}
	else {
		glm::vec3 center = glm::vec3(0.0, -height/2.0, 0.0);
		y = -height/2.0;
	}

	//add circle center
	vertices.push_back(Vertex(center, color, glm::vec2(0.5f,  0.5f)));

	//vertices on circumference
	for (float i = 0.0f; i < 360.0f; i += (360.0f / slices)) {
		vertices.push_back(Vertex(glm::vec3(radius * cosf(i * M_PI/180.0), y, radius * sinf(i*M_PI/180.0)), color, glm::vec2(cosf(i * M_PI / 180.0), sinf(i*M_PI / 180.0))));
	}
}

void Cylinder::genIndices(std::vector<GLuint> &indices) {

	//top circle divided on triangular slices
	for (unsigned int i = 0; i < slices; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		if (i + 1 == slices)
			indices.push_back(1);
		else
			indices.push_back(i + 2);

		//bottom circle
		indices.push_back(slices + 1);
		indices.push_back(slices + 2 + i);
		if (i + 1 == slices)
			indices.push_back(slices + 2);
		else
			indices.push_back(slices + 3 + i);
	}

	//side of cylinder
	for (unsigned int i = 1; i < slices; i++) {
		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices + 2);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + slices + 2);
	}
}