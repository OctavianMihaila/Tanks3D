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
    this->ttl = 4.0f;
    this->gravity = 9.8f;
    this->destroy = false;

    if (isBallistic) {
        velocity = cannonRotationAngle * glm::vec3(-glm::degrees(turretRotationAngle), 20.0f, -20.0f);
    } else {
        velocity = cannonRotationAngle * glm::vec3(-glm::degrees(turretRotationAngle), 0.0f, -0.0f);
    }
}

Shell::Shell() {}

Shell::~Shell() {}

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

        // Rotate the shell based on the velocity.
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),
                                                glm::radians(glm::degrees(glm::atan(velocity.x, velocity.z))),
                                                glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotatedDirection = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(velocity, 0.0f)));
    }
    else {
        // Calculate the direction based on the turretRotationAngle.
        glm::vec3 direction = glm::normalize(glm::vec3(
            -sin(glm::radians(turretRotationAngle)),
            0.0f,
            -cos(glm::radians(turretRotationAngle))
        ));

        // Rotate the direction vector based on turret rotation.
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotatedDirection = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(direction, 0.0f)));

        // Update the position to move in the direction of the rotated vector.
        position += rotatedDirection * 10.0f * deltaTime;
    }

    if (position.y <= 0.0f || ttl < 0 || hasCollidedWithTank) {
        destroy = true;
    }

    ttl -= deltaTime;
}

bool Shell::getHasCollidedWithTank() {
    return hasCollidedWithTank;
}

float Shell::getRotationAngle() {
	return turretRotationAngle;
}


bool Shell::shouldDestroy() {
    return destroy;
}
