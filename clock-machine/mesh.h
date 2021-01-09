#pragma once

#include<vector>
#include "Vertex.h"
#include<GL/glew.h>

class Mesh
{
private:
	//std::vector<Vertex> *vertices = new std::vector<Vertex>();
	//std::vector<GLuint> *indices = new std::vector<GLuint>();
	GLuint VAO, EBO, VBO;
	GLsizei indicesNum;

protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) = 0;

public:
	Mesh();
	~Mesh();
	void init();
	void draw() const;
};

