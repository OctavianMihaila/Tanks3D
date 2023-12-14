#include "turret.h"

Turret::Turret(Mesh* mesh, glm::vec3 color) {
	rotationAngle = 0;
	this->mesh = mesh;
	this->color = color;
}

Turret::Turret() {
	rotationAngle = 0;
}

Turret::~Turret() {}

float Turret::getRotationAngle() const {
	return rotationAngle;
}

glm::vec3 Turret::getColor() {
	return color;
}

void Turret::setRotationAngle(float angle) {
	rotationAngle = angle;
}