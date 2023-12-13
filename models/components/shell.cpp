// Shell.cpp
#include "shell.h"

Shell::Shell(Mesh* mesh, glm::vec3 startingPosition, float cannonRotationAngle, float turretRotationAngle, bool isBallistic, bool isEnemy) {
	mesh = mesh;
    position = startingPosition;
    this->isBallistic = isBallistic;
    this->turretRotationAngle = turretRotationAngle;
    this->cannonRotationAngle = cannonRotationAngle;
    this->boundingBoxSize = glm::vec3(0.4f, 0.4f, 0.4f);
    this->enemy = isEnemy;
    this->hasCollidedWithTank = false;

    if (isBallistic) {
        velocity = cannonRotationAngle * glm::vec3(-glm::degrees(turretRotationAngle), 20.0f, -20.0f);
    } else {
        velocity = cannonRotationAngle * glm::vec3(-glm::degrees(turretRotationAngle), 0.0f, -0.0f);
    }
   
    ttl = 3.0f;
    gravity = 9.8f;
    destroy = false;
}

Shell::Shell() {
}

Shell::~Shell() {
}

void Shell::setPosition(glm::vec3 position) {
    this->position = position;
    this->velocity = glm::vec3(0.0f);
    this->destroy = false;
}

void Shell::setHasCollided(bool state) {
	hasCollidedWithTank = state;
}

glm::vec3 Shell::getPosition() {
    return position;
}

glm::vec3 Shell::getBoundingBoxSize() {
    return boundingBoxSize;
}

bool Shell::isEnemy() {
	return enemy;
}

void Shell::update(float deltaTime) {
    if (isBallistic) {
        velocity.y -= gravity * deltaTime;
        position += velocity * deltaTime;
    }
    else {
        glm::vec3 direction = glm::normalize(glm::vec3(
            -sin(glm::radians(turretRotationAngle) * 55.0f),
            0.0f,
            -cos(glm::radians(turretRotationAngle) * 55.0f)
        ));

        // update it so that it moves in the direction of the cannon
        position += direction * 10.0f * deltaTime;

    }

    // destroy when reaches the ground
    if (position.y <= 0.0f || ttl < 0 || hasCollidedWithTank) {
        destroy = true;
    }

    ttl -= deltaTime;
}

bool Shell::getHasCollidedWithTank() {
    return hasCollidedWithTank;
}


bool Shell::shouldDestroy() {
    return destroy;
}
