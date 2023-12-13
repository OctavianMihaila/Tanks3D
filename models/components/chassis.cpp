// Chassis.cpp
#include "Chassis.h"

Chassis::Chassis(glm::vec3 track_color, glm::vec3 body_color) {
	rotationAngle = 0;
	this->track_color = track_color;
	this->body_color = body_color;
	this->bodyDamaged = false;
	this->trackDamageLevel = 0;
}

Chassis::Chassis() {
	rotationAngle = 0;
}

Chassis::~Chassis() {
    // Clean up resources
}

float Chassis::getRotationAngle() {
	return rotationAngle;
}

glm::vec3 Chassis::getTrackColor() {
	return track_color;
}

glm::vec3 Chassis::getBodyColor() {
	return body_color;
}

int Chassis::getTrackDamageLevel() {
	return trackDamageLevel;
}

bool Chassis::isBodyDamaged() {
	return bodyDamaged;
}

void Chassis::setBodyDamaged(bool damaged) {
	bodyDamaged = damaged;
}

void Chassis::setRotationAngle(float angle) {
	rotationAngle = angle;
}

void Chassis::IncrementTrackDamageLevel() {
	trackDamageLevel++;
}