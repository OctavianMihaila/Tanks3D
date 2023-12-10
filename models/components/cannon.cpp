// Cannon.cpp
#include "Cannon.h"

Cannon::Cannon(Mesh* mesh) {
    rotationAngle = 0;
	mesh = mesh;
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

void Cannon::setRotationAngle(float angle) {
	rotationAngle = angle;
}

//void Cannon::incrementRotationAngle(float angle) {
//	rotationAngle += angle;
//}
//
//void Cannon::decrementRotationAngle(float angle) {
//	rotationAngle -= angle;
//}