// Cannon.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Cannon {
public:
    Cannon();
    Cannon(Mesh* mesh, glm::vec3 color);
    ~Cannon();

    float getRotationAngle();
    glm::vec3 getColor();
    void setRotationAngle(float angle);

private:
    Mesh *mesh;
    glm::vec3 color;
    float rotationAngle;
};