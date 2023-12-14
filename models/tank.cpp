// Tank.cpp
#include "Tank.h"

Tank::Tank(Chassis chassis, Turret turret, Cannon cannon, bool isEnemy, glm::vec3 color) {
    this->chassis = chassis;
    this->turret = turret;
    this->cannon = cannon;
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->color = color;
	this->boundingBoxSize = glm::vec3(1.0f, 1.0f, 1.0f);
	this->moving = false;
	this->aiming = false;
	this->followingPlayer = false;
	this->pointsCounted = false;
	this->hp = 100.0f;
	this->cooldown = 1.0f;
	this->enemy = isEnemy;
	this->stateChangeInterval = 6.0f;

	if (isEnemy) {
		int randomState = rand() % 4;

		determinateInitialState(randomState);
	}
}

Tank::Tank() {}

Tank::~Tank() {
}

glm::vec3 Tank::getPosition() {
	return position;
}

glm::vec3 Tank::getColor() {
	return color;
}

float Tank::getHp() {
	return hp;
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

glm::vec3 Tank::getBoundingBoxSize() const {
	return boundingBoxSize;
}

bool Tank::isMoving() {
	return moving;
}

bool Tank::isAiming() {
	return aiming;
}

bool Tank::isTimeToChangeState() {
	if (stateChangeInterval <= 0.0f) {
		stateChangeInterval = 6.0f;
		
		return true;
	}

	return false;
}

bool Tank::isTimeToShoot() {
	if (cooldown <= 0.0f) {
		if (enemy) {
			cooldown = 3.0f;
		}
		else {
			cooldown = 1.0f;
		}

		return true;
	}

	return false;
}

bool Tank::isFollowingPlayer() {
	return followingPlayer;
}

bool Tank::isDestroyed() {
	return hp <= 0.0f;
}

bool Tank::isEnemy() {
	return enemy;
}

bool Tank::arePointsCounted() {
	return pointsCounted;
}

void Tank::setMovingState(bool state, int movingPosition) {
	moving = state;
	movingDirection = movingPosition;
}

void Tank::setFollowingPlayer(bool state) {
	followingPlayer = state;
}

void Tank::setMovementState(RandomMovementService::MovementState state) {
	currentMovementState = state;
}

void Tank::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void Tank::setDamagedComponents(int HP) {
	switch (HP) {
		case 100:
			chassis.setBodyDamaged(true);
			break;
		case 65:
			chassis.IncrementTrackDamageLevel();
			break;
		case 30:
			chassis.IncrementTrackDamageLevel();
			break;
		case 0:
			break;
		default:
			break;
	}
}

void Tank::setPointsCounted(bool state) {
	pointsCounted = state;
}

void Tank::deacreaseHp(float damage) {
	hp -= damage;
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

void Tank::determinateInitialState(int randomState) {
	switch (randomState) {
	case 0:
		currentMovementState = RandomMovementService::MovementState::GoingForward;
		setMovingState(true, FORWARD);
		break;
	case 1:
		currentMovementState = RandomMovementService::MovementState::GoingBackward;
		setMovingState(true, BACKWARD);
		break;
	case 2:
		currentMovementState = RandomMovementService::MovementState::InPlaceRotationLeft;
		setMovingState(true, LEFT);
		break;
	case 3:
		currentMovementState = RandomMovementService::MovementState::InPlaceRotationRight;
		setMovingState(true, RIGHT);
		break;
	default:
		break;
	}
}

void Tank::generateEnemyMoves(float deltaTime) {
	if (enemy) {
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

void Tank::move(float deltaTime, bool gameStatus) {
	if (isDestroyed() || gameStatus == FINISHED) { // Destroyed tanks can't move
		return;
	}

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
	if (enemy) {
		// Calculate direction from enemy tank to player tank
		glm::vec3 direction = glm::normalize(playerTank->getPosition() - position);
	
		float turretRotation = atan2(direction.x, direction.z) + glm::radians(180.0f);
		turret.setRotationAngle(turretRotation);
	}
}

Shell* Tank::launchShell(Mesh* mesh, bool isBallistic) {
	// Calculate the starting position of the shell. It should be the end of the cannon
	float cannonAngleOffset = cannon.getRotationAngle() * 0.2f;
	
	// calulate z based on rotation angle of the turret

	glm::vec3 startPosition = position + glm::vec3(0.0f, 0.4f + cannonAngleOffset, 0.0f) + cannon.getRotationAngle() * 0.05f;

	// Enemy tanks should not be able to shoot shells that are too far away from them
	if (enemy) {
		if (std::abs(position.x - startPosition.x) > 7.0f || std::abs(position.z - startPosition.z) > 7.0f) {
			return nullptr;
		}
	}

	// Create and return the shell
	Shell* shell = new Shell(mesh, startPosition, cannon.getRotationAngle(), turret.getRotationAngle(), isBallistic, enemy);
	return shell;
}
