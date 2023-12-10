#include "turret.h"

Turret::Turret(Mesh* mesh) {
	rotationAngle = 0;
	mesh = mesh;
}

Turret::Turret() {
	rotationAngle = 0;
}

Turret::~Turret() {
    // Clean up resources
}

float Turret::getRotationAngle() const {
	return rotationAngle;
}

void Turret::setRotationAngle(float angle) {
	rotationAngle = angle;
}