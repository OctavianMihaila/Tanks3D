// Shell.h
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Shell {
public:
    Shell::Shell(Mesh* mesh, glm::vec3 startingPosition, float cannonRotationAngle, float turretRotationAngle, bool isBallistic, bool isEnemy);
    Shell();
    ~Shell();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    glm::vec3 getBoundingBoxSize();
    bool getHasCollidedWithTank();
    void setHasCollided(bool state);

    void update(float deltaTime);

    bool isEnemy();
    bool shouldDestroy();

private:
    Mesh* mesh;
    glm::vec3 position;

    glm::vec3 velocity;
    glm::vec3 boundingBoxSize;
    float gravity;
    float turretRotationAngle;
    float cannonRotationAngle;
    float ttl;

    bool enemy;
    bool destroy;
    bool isBallistic;
    bool hasCollidedWithTank;
};
