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
#define FINISHED true

class Tank {
public:
    Tank(Chassis chassis, Turret turret, Cannon cannon, bool isEnemy, glm::vec3 color);
    void determinateInitialState(int randomState);
    Tank();
    ~Tank();

    glm::vec3 getPosition();
    glm::vec3 getColor();
    float getHp();
    bool isMoving();
    bool isAiming();
    bool isTimeToChangeState();
    bool isFollowingPlayer();
    bool isDestroyed();
    bool getMoving();
    bool isTimeToShoot();
    bool isEnemy();
    int getMovingDirection();
    glm::vec3 getBoundingBoxSize() const;
    RandomMovementService::MovementState getCurrentMovementState();
    Chassis* getChassis();
    Turret* getTurret();
    Cannon* getCannon();
    void setMovingState(bool state, int movingPosition);
    void setPosition(glm::vec3 position);
    void deacreaseHp(float damage);
    void decreaseStateChangeInterval(float deltaTime);
    void deacreaseCooldown(float deltaTime);
    void setDamagedComponents(int HP);
    void setCannonAimingState(bool state, int cannonPosition);
    void setFollowingPlayer(bool state);
    void setMovementState(RandomMovementService::MovementState state);
    void generateEnemyMoves(float deltaTime);
    void move(float deltaTime, bool gameStatus);
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
    glm::vec3 boundingBoxSize;
    glm::vec3 color;
    //float rotation;
    bool moving;
    bool aiming;
    bool enemy;
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
