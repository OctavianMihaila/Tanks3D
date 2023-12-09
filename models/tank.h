// Tank.h
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "components/chassis.h"
#include "components/Turret.h"
#include "components/Cannon.h"

#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4
#define UP 5
#define DOWN 6
#define TANK_SPEED 3.0f
#define TANK_ROTATION_SPEED 1.0f
#define TANK_AIMING_SPEED 0.3f

class Tank {
public:
    Tank(Chassis chassis, Turret turret, Cannon cannon);
    Tank();
    ~Tank();

    glm::vec3 getPosition();
    bool isMoving();
    bool isAiming();
    bool getMoving();
    int getMovingDirection();
    Chassis* getChassis();
    Turret* getTurret();
    Cannon* getCannon();
    void setMovingState(bool state, int movingPosition);
    void setCannonAimingState(bool state, int cannonPosition);
    void move(float deltaTime);
    void aim(float deltaTime);

private:
    // Tank components
    Chassis chassis;
    Turret turret;
    Cannon cannon;

    // Tank properties
    glm::vec3 position;
    //float rotation;
    bool moving;
    bool aiming;
    // add moving direction attribute
    int movingDirection;
    int cannonDirection;
};
