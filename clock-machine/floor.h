#pragma once

#include "vertex.h"
#include "mesh.h"
#include <vector>


class Floor : public Mesh
{
protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);
};

