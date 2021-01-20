#pragma once

#include<vector>
#include <iostream>
#include <SOIL.h>
#include<GL/glew.h>
#include "Vertex.h"

class Mesh
{
private:
	//std::vector<Vertex> *vertices = new std::vector<Vertex>();
	//std::vector<GLuint> *indices = new std::vector<GLuint>();
	GLuint VAO, EBO, VBO;
	GLsizei indicesNum;
	GLuint texture;

protected:
	virtual void setVertices(std::vector<Vertex> &vertices, std::vector<GLuint> &indices) = 0;

public:
	Mesh();
	~Mesh();
	void init();
	void loadTexture(const char* fname);
	void draw() const;
};

