#pragma once
#define _USE_MATH_DEFINES


#include "vertex.h"
#include "mesh.h"
#include <vector>
#include <cmath>


class HalfSphere
{
private:
	GLuint slices;
	GLfloat radius;

protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

public:
	HalfSphere( float _radius);
};

