#include "drawer.h"

Drawer::Drawer() {};

void Drawer::useCommonShader(glm::mat4 view, glm::mat4 projection, double brightness) {
	glDepthFunc(GL_LESS); // set depth function back to default

	commonShader->Use();
	commonShader->setVec3("lightColor", glm::vec3(brightness));
	commonShader->setMat4("projection", projection);
	commonShader->setMat4("view", view);
};

void Drawer::useSkyboxShader(glm::mat4 view, glm::mat4 projection) {
	glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content

	skyboxShader->Use();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setMat4("view", view);
};

void Drawer::drawCover(Mesh *cover) {
	model = glm::mat4(1.0f);
	tranformation.translate(model, 0, 0.5, -0.5);
	tranformation.rotate(model, 1, 0, 0, 90);
	tranformation.scale(model, 1, 1, 1);

	commonShader->setMat4("model", model);

	cover->draw();
};

void Drawer::drawFrontOfClock(Mesh *frontOfClock) {
	model = glm::mat4(1.0f);

	tranformation.translate(model, 0, 0.5, -0.5);
	tranformation.rotate(model, 1, 0, 0, 90);
	tranformation.scale(model, 1, 1, 1);

	commonShader->setMat4("model", model);
	frontOfClock->draw();
};

void Drawer::drawPlug(Mesh *plug) {
	model = glm::mat4(1.0f);

	tranformation.translate(model, 0, 0.5, -0.3);
	tranformation.rotate(model, 1, 0, 0, 90);
	tranformation.scale(model, 1, 1, 1);

	commonShader->setMat4("model", model);
	plug->draw();
};

void Drawer::drawMinutePointer(Mesh *pointer, double *animationSpeed, static GLfloat *pointerAngel) {
	model = glm::mat4(1.0f);

	*pointerAngel -= 0.12 * *animationSpeed;
	if (*pointerAngel <= -360)
		*pointerAngel = 0.0f;

	tranformation.translate(model, 0, 0.5, -0.25);
	tranformation.rotate(model, 0, 0, 1, *pointerAngel);
	tranformation.scale(model, 0.2, 0.8, 0.8);

	commonShader->setMat4("model", model);
	pointer->draw();
};

void Drawer::drawHourPointer(Mesh *pointer, double *animationSpeed, static GLfloat *pointerAngel)
{
	model = glm::mat4(1.0f);

	*pointerAngel -= 0.01 * *animationSpeed;

	if (*pointerAngel <= -360)
		*pointerAngel = 0.0f;

	tranformation.translate(model, 0, 0.5, -0.28);
	tranformation.rotate(model, 0, 0, 1, *pointerAngel);
	tranformation.scale(model, 0.4, 0.6, 0.8);

	commonShader->setMat4("model", model);
	pointer->draw();
}

void Drawer::drawFirstBell(Mesh *bell)
{
	model = glm::mat4(1.0f);

	tranformation.translate(model, 0.25, 1, -0.5);
	tranformation.rotate(model, 0, 0, 1, -30);
	tranformation.scale(model, 1, 1, 1);

	commonShader->setMat4("model", model);
	bell->draw();
};

void Drawer::drawSecondBell(Mesh *bell)
{
	model = glm::mat4(1.0f);

	tranformation.translate(model, -0.25, 1, -0.5);
	tranformation.rotate(model, 0, 0, 1, 30);
	tranformation.scale(model, 1, 1, 1);

	commonShader->setMat4("model", model);
	bell->draw();
};

void Drawer::drawCube(Mesh *cube)
{
	model = glm::mat4(1.0f);

	tranformation.translate(model, 0, -0.5, -0.5);
	commonShader->setMat4("model", model);
	cube->draw();
};

void Drawer::drawFloor(Mesh *floor) 
{
	model = glm::mat4(1.0f);

	tranformation.translate(model, 0, -1.5, -1.5);
	tranformation.scale(model, 100, 1, 100);
	commonShader->setMat4("model", model);
	floor->draw();
};

void Drawer::drawSkybox(Mesh *skybox, Environment *environment)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, environment->getTexture());
	skybox->draw();
}