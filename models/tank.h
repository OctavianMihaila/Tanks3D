// Tank.h
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "components/chassis.h"
#include "components/turret.h"
#include "components/cannon.h"
#include "components/shell.h"
#include "../services/movement/random_movement_service.h"

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
    Tank(Chassis chassis, Turret turret, Cannon cannon, bool isEnemy);
    Tank();
    ~Tank();

    glm::vec3 getPosition();
    bool isMoving();
    bool isAiming();
    bool isTimeToChangeState();
    bool isFollowingPlayer();
    bool getMoving();
    bool isTimeToShoot();
    int getMovingDirection();
    RandomMovementService::MovementState getCurrentMovementState();
    Chassis* getChassis();
    Turret* getTurret();
    Cannon* getCannon();
    void setMovingState(bool state, int movingPosition);
    void setPosition(glm::vec3 position);
    void decreaseStateChangeInterval(float deltaTime);
    void deacreaseCooldown(float deltaTime);
    void setCannonAimingState(bool state, int cannonPosition);
    void setFollowingPlayer(bool state);
    void generateEnemyMoves(float deltaTime);
    void move(float deltaTime);
    void aim(float deltaTime);
    void followPlayerWithTurret(Tank* playerTank);
    Shell* launchShell(Mesh* mesh, bool isBallistic);
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
    bool isEnemy;
    bool followingPlayer;
    // add moving direction attribute
    int movingDirection;
    int cannonDirection;
    RandomMovementService::MovementState currentMovementState;
    RandomMovementService randomMovementService;
    float hp;
    float stateChangeInterval;
    float cooldown;
};
