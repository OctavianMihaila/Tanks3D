// Cannon.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Cannon {
public:
    Cannon();
    ~Cannon();

    float getRotationAngle();
    void setRotationAngle(float angle);
    //void incrementRotationAngle(float angle);
    //void decrementRotationAngle(float angle);

private:
    Mesh *mesh;
    float rotationAngle;
};