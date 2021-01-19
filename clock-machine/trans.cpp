#include "trans.h"

Trans::Trans() {
}

void Trans::translate(glm::mat4 &model, float x, float y, float z) {
	model = glm::translate(model, glm::vec3(x, y, z));
}

void Trans::scale(glm::mat4 &model, float x, float y, float z) {
	model = glm::scale(model, glm::vec3(x, y, z));
}
void Trans::rotate(glm::mat4 &model, float x, float y, float z, float angle) {
	model = glm::rotate(model, glm::radians(angle), glm::vec3(x, y, z));
}


