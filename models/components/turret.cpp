#include "turret.h"

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