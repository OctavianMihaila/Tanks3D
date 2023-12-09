// Tank.cpp
#include "Tank.h"

Tank::Tank(Chassis chassis, Turret turret, Cannon cannon) {
    chassis = chassis;
    turret = turret;
    cannon = cannon;
    position = glm::vec3(0.0f, 0.0f, 0.0f);
	moving = false;
	aiming = false;
}

Tank::Tank() {}

Tank::~Tank() {
}

glm::vec3 Tank::getPosition() {
	return position;
}

int Tank::getMovingDirection() {
	if (movingDirection == FORWARD) {
		return 1;
	}
	
	if (movingDirection == BACKWARD) {
		return -1;
	}

	return 0;
}

Chassis* Tank::getChassis() {
	return &chassis;
}

Turret* Tank::getTurret() {
	return &turret;
}

Cannon* Tank::getCannon() {
	return &cannon;
}

bool Tank::isMoving() {
	return moving;
}

bool Tank::isAiming() {
	return aiming;
}

void Tank::setMovingState(bool state, int movingPosition) {
	moving = state;
	movingDirection = movingPosition;
}

void Tank::setCannonAimingState(bool state, int cannonPosition) {
	aiming = state;
	cannonDirection = cannonPosition;
}

void Tank::move(float deltaTime) {
	float newRotation;

    switch (movingDirection) {
        case FORWARD:
			position.x -= TANK_SPEED * deltaTime * sin(chassis.getRotationAngle());
			position.z -= TANK_SPEED * deltaTime * cos(chassis.getRotationAngle());
			break;
		case BACKWARD:
			position.x += TANK_SPEED * deltaTime * sin(chassis.getRotationAngle());
			position.z += TANK_SPEED * deltaTime * cos(chassis.getRotationAngle());
			break;
		case LEFT:
			newRotation = chassis.getRotationAngle() + TANK_ROTATION_SPEED * deltaTime;
			chassis.setRotationAngle(newRotation);
			break;
		case RIGHT:
			newRotation = chassis.getRotationAngle() - TANK_ROTATION_SPEED * deltaTime;
			chassis.setRotationAngle(newRotation);
			break;
		default:
			std::cout << "Invalid moving direction!\n";
			break;
    }
}

void Tank::aim(float deltaTime) {
	float newRotation;

	switch (cannonDirection) {
	case UP:
		newRotation = cannon.getRotationAngle() + TANK_AIMING_SPEED * deltaTime;
		break;
	case DOWN:
		newRotation = cannon.getRotationAngle() - TANK_AIMING_SPEED * deltaTime;
		break;
	default:
		std::cout << "Invalid cannon direction!\n";
		break;
	}

	if (newRotation > 0.5f || newRotation < 0.0f) {
		aiming = false;
	}

	cannon.setRotationAngle(newRotation);
}	