#pragma once

#include "trans.h"
#include "mesh.h"
#include "shprogram.h"
#include "environment.h"

class Drawer
{
	ShaderProgram *commonShader = new ShaderProgram("clock_machine.vert", "clock_machine.frag");
	ShaderProgram *skyboxShader = new ShaderProgram("skybox.vert", "skybox.frag");

	Trans tranformation;
	glm::mat4 model;

public:
	Drawer();
	void useCommonShader(glm::mat4 view, glm::mat4 projection, double brightness);
	void useSkyboxShader(glm::mat4 view, glm::mat4 projection);
	void drawCover(Mesh *cover);
	void drawFrontOfClock(Mesh *frontOfClock);
	void drawPlug(Mesh *plug);
	void drawMinutePointer(Mesh *pointer, double *animationSpeed,  static GLfloat *pointerAngel);
	void drawHourPointer(Mesh *pointer, double *animationSpeed, static GLfloat *pointerAngel);
	void drawFirstBell(Mesh *plug);
	void drawSecondBell(Mesh *plug);
	void drawCube(Mesh *cube);
	void drawFloor(Mesh *floor);
	void drawSkybox(Mesh *skybox, Environment *environment);
};