#pragma once

#include "vertex.h"
#include "mesh.h"
#include <vector>


class Cube : public Mesh
{
protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

public:
	//std::vector<Vertex> getVertices();
	//std::vector<GLuint> getIndices();
};

