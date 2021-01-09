#pragma once
#define _USE_MATH_DEFINES


#include "vertex.h"
#include "mesh.h"
#include <vector>
#include <cmath>




class Cylinder : public Mesh
{
private:
	GLuint slices;
	GLfloat radius;
	GLfloat height;

	void genVertices(std::vector<Vertex> &vertices, bool isTop);
	void genIndices(std::vector<GLuint> &indices);
protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

public:
	Cylinder();
};

