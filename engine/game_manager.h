#pragma once

#include <vector>
#include "../models/tank.h"
#include "../models/components/shell.h"
#include "../models/buildings/barracks.h"
#include "../services/collision/collision_handler_service.h"

#define MAP_SIZE_X 25.0f
#define MAP_SIZE_Z 25.0f

class GameManager {
public:
    GameManager();

    // Functions to add tanks, player tank, bullets, etc.
    std::vector<Shell*> getEnemyBullets();
    std::vector<Shell*> getPlayerBullets();
    std::vector<Tank*> getEnemyTanks();
    std::vector<Barracks*> getBarracksList();
    bool isGameFinished();
    void AddTank(Tank* tank);
    void RemoveBullet(Shell* bullet);
    void SetPlayerTank(Tank* playerTank);
    void AddBullet(Shell* bullet, bool isEnemy);
    void AddBarracks(Barracks* barracks);
    void RemoveBullet(Shell *bullet, bool isEnemy);
    void RemoveDestroyedTanks();
    bool CheckPositionIsEmpty(glm::vec3 position, float areaX, float areaZ);

    // Update function to update the game state
    void Update(float deltaTime);

private:
    // Container for tanks, player tank, bullets, etc.
    int score;
    float timeLeft;
    bool gameFinished;

    Tank *playerTank;
    std::vector<Tank*> enemyTanks;
    std::vector<Shell*> playerBullets;
    std::vector<Shell*> enemyBullets;
    std::vector<Barracks*> barracksList;

    CollisionHandlerService collisionHandlerService;
};