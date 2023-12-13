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
    bool isBodyDamaged();
    void setBodyDamaged(bool damaged);
    glm::vec3 getTrackColor();
    glm::vec3 getBodyColor();
    void setRotationAngle(float angle);
    void IncrementTrackDamageLevel();
    int getTrackDamageLevel();

private:
    float rotationAngle;
    bool bodyDamaged;
    int trackDamageLevel;
    Mesh *track_mesh;
    Mesh *body_mesh;
    glm::vec3 track_color;
    glm::vec3 body_color;
};