
#pragma once
#define _USE_MATH_DEFINES


#include "vertex.h"
#include "mesh.h"
#include <vector>
#include <cmath>




class Cover : public Mesh
{
private:
	GLuint slices;
	GLfloat radius;
	GLfloat height;
	GLfloat thickness;

	void genVertices(std::vector<Vertex> &vertices);
	void genIndices(std::vector<GLuint> &indices);
protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

public:
	Cover(int _slices, float _radius, float _height, float thickness);
};


