// Chassis.cpp
#include "Chassis.h"

Chassis::Chassis() {
	rotationAngle = 0;
}

Chassis::~Chassis() {
    // Clean up resources
}

float Chassis::getRotationAngle() {
	return rotationAngle;
}

void Chassis::setRotationAngle(float angle) {
	rotationAngle = angle;
}