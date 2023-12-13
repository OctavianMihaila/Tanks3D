// Turret.h
#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Turret {
public:
    Turret();
    Turret::Turret(Mesh* mesh, glm::vec3 color);
    ~Turret();

    float getRotationAngle() const;
    glm::vec3 getColor();
    void setRotationAngle(float angle);
private:
    float rotationAngle;
    Mesh *mesh;
    glm::vec3 color;
};

