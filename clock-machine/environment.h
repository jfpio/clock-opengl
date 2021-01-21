#pragma once

class Environment
{
	unsigned int texture;

	std::vector<std::string> faces{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg" };

	unsigned int loadCubemap();

public:
	Environment();
	unsigned int getTexture();
};