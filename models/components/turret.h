// Turret.h
#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Turret {
public:
    Turret();
    ~Turret();

    float getRotationAngle() const;
    void setRotationAngle(float angle);
private:
    float rotationAngle;
    Mesh *mesh;
};

