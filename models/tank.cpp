// Tank.cpp
#include "Tank.h"

Tank::Tank(Chassis chassis, Turret turret, Cannon cannon, bool isEnemy) {
    this->chassis = chassis;
    this->turret = turret;
    this->cannon = cannon;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->moving = false;
	this->aiming = false;
	this->followingPlayer = false;
	this->hp = 100.0f;
	this->cooldown = 2.0f;
	this->isEnemy = isEnemy;
	this->stateChangeInterval = 4.0f;

	if (isEnemy) {
		currentMovementState = RandomMovementService::MovementState::GoingForward;
		setMovingState(true, FORWARD);
	}
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

RandomMovementService::MovementState Tank::getCurrentMovementState() {
	return currentMovementState;
}

bool Tank::isMoving() {
	return moving;
}

bool Tank::isAiming() {
	return aiming;
}

bool Tank::isTimeToChangeState() {
	if (stateChangeInterval <= 0.0f) {
		stateChangeInterval = 4.0f;
		
		return true;
	}

	return false;
}

bool Tank::isTimeToShoot() {
	if (cooldown <= 0.0f) {
		cooldown = 2.0f;

		return true;
	}

	return false;
}

bool Tank::isFollowingPlayer() {
	return followingPlayer;
}

void Tank::setMovingState(bool state, int movingPosition) {
	moving = state;
	movingDirection = movingPosition;
}

void Tank::setFollowingPlayer(bool state) {
	followingPlayer = state;
}

void Tank::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void Tank::decreaseStateChangeInterval(float deltaTime) {
	stateChangeInterval -= deltaTime;
}

void Tank::deacreaseCooldown(float deltaTime) {
	cooldown -= deltaTime;
}

void Tank::setCannonAimingState(bool state, int cannonPosition) {
	aiming = state;
	cannonDirection = cannonPosition;
}

void Tank::generateEnemyMoves(float deltaTime) {
	if (isEnemy) {
		// If the tank is an enemy, update its movement randomly
		currentMovementState = randomMovementService.GetNextMovementState(currentMovementState);

		// Update the tank's movement direction based on the random state
		switch (currentMovementState) {
			case RandomMovementService::MovementState::GoingForward:
				setMovingState(true, FORWARD);
				break;
			case RandomMovementService::MovementState::GoingBackward:
				setMovingState(true, BACKWARD);
				break;
			case RandomMovementService::MovementState::InPlaceRotationLeft:
				setMovingState(true, LEFT);
				break;
			case RandomMovementService::MovementState::InPlaceRotationRight:
				setMovingState(true, RIGHT);
				break;
			case RandomMovementService::MovementState::FollowPlayerWithTurret:
				followingPlayer = true;
				break;
			
			default:
				break;
		}
	}
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

void Tank::followPlayerWithTurret(Tank* playerTank) {
	if (isEnemy) {
		// Calculate direction from enemy tank to player tank
		glm::vec3 direction = glm::normalize(playerTank->getPosition() - position);

		//// Set turret rotation to aim at the player tank
		//float turretRotation = atan2(direction.x, direction.z);
		//turret.setRotationAngle(turretRotation);

		// with the above two lines it points the opposite direction of the player tank
		// so we need to rotate it 180 degrees
		float turretRotation = atan2(direction.x, direction.z) + glm::radians(180.0f);
		turret.setRotationAngle(turretRotation);
	}
}

Shell* Tank::launchShell(Mesh* mesh, bool isBallistic) {
	// Calculate the starting position of the shell. It should be the end of the cannon
	float cannonAngleOffset = cannon.getRotationAngle() * 0.2f;

	glm::vec3 startPosition = position + glm::vec3(-0.2f, 0.4f + cannonAngleOffset, 0.0f) + cannon.getRotationAngle() * 0.05f;

	// Create and return the shell
	Shell* shell = new Shell(mesh, startPosition, cannon.getRotationAngle(), turret.getRotationAngle(), isBallistic);
	return shell;
}
