// Shell.h
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Shell {
public:
    Shell(Mesh* mesh, glm::vec3 startingPosition, float cannonRotationAngle, float turretRotationAngle, bool isBallistic);
    Shell();
    ~Shell();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();

    void update(float deltaTime);

    bool shouldDestroy();

private:
    Mesh* mesh;
    glm::vec3 position;

    glm::vec3 velocity;
    float gravity;
    float turretRotationAngle;
    float cannonRotationAngle;
    float ttl;

    bool destroy;
    bool isBallistic;
};
