// Chassis.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Chassis {
public:
    Chassis::Chassis();
    Chassis(glm::vec3 track_color, glm::vec3 body_color);
    ~Chassis();

    float getRotationAngle();
    glm::vec3 getTrackColor();
    glm::vec3 getBodyColor();
    int getTrackDamageLevel();
    void setBodyDamaged(bool damaged);
    void setRotationAngle(float angle);
    bool isBodyDamaged();
    void IncrementTrackDamageLevel();

private:
    float rotationAngle;
    bool bodyDamaged;
    int trackDamageLevel;
    Mesh *track_mesh;
    Mesh *body_mesh;
    glm::vec3 track_color;
    glm::vec3 body_color;
};