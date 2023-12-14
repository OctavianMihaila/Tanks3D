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

    glm::vec3 getPosition();
    glm::vec3 getBoundingBoxSize();
    bool getHasCollidedWithTank();
    float getRotationAngle();
    void setHasCollided(bool state);
    void setPosition(glm::vec3 position);
    bool isEnemy();
    bool shouldDestroy();
    void update(float deltaTime);

private:
    float gravity;
    float turretRotationAngle;
    float cannonRotationAngle;
    float ttl;
    bool enemy;
    bool destroy;
    bool isBallistic;
    bool hasCollidedWithTank;
    Mesh* mesh;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 boundingBoxSize;
};
