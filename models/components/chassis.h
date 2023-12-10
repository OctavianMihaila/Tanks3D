// Chassis.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Chassis {
public:
    Chassis::Chassis();
    Chassis(Mesh* mesh);
    ~Chassis();

    float getRotationAngle();
    void setRotationAngle(float angle);

private:
    float rotationAngle;
    Mesh *track_mesh;
    Mesh *body_mesh;
};