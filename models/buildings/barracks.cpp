#include "barracks.h"

Barracks::Barracks(Mesh* mesh, glm::vec3 position, std::string name) {
	this->mesh = mesh;
	this->position = position;
	this->name = name;
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

std::string Barracks::getName() {
	return name;
}

glm::vec3 Barracks::getBoundingBoxSize() {
	if (name == "vertical_barracks") {
		return glm::vec3(5.8f, 2.5f, 2.8f);
	}
	else if (name == "horizontal_barracks") {
		return glm::vec3(2.8f, 2.5f, 5.8f);
	}
	else {
		return glm::vec3(2.8f, 2.5f, 5.8f);
	}
}
