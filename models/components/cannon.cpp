// Cannon.cpp
#include "Cannon.h"

Cannon::Cannon(Mesh* mesh, glm::vec3 color) {
    rotationAngle = 0;
	this->mesh = mesh; // TODO: check if useless
	this->color = color;
}

Cannon::Cannon() {
	rotationAngle = 0;
}

Cannon::~Cannon() {
    // Clean up resources
}

float Cannon::getRotationAngle() {
	return rotationAngle;
}

glm::vec3 Cannon::getColor() {
	return color;
}

void Cannon::setRotationAngle(float angle) {
	rotationAngle = angle;
}

