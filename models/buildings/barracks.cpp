#include "barracks.h"

Barracks::Barracks(Mesh* mesh, glm::vec3 position) {
	this->mesh = mesh;
	this->position = position;
	this->boundingBox = glm::vec3(3.0f, 2.5f, 6.0f);
}

Barracks::Barracks() {
}

Barracks::~Barracks() {
	// Clean up resources
}

glm::vec3 Barracks::getPosition() {
	return position;
}

glm::vec3 Barracks::getBoundingBoxSize() {
	return boundingBox;
}
