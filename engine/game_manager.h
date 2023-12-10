#pragma once

#include <vector>
#include "../models/tank.h"
#include "../models/components/shell.h"

#define MAP_SIZE_X 25.0f
#define MAP_SIZE_Z 25.0f

class GameManager {
public:
    GameManager();

    // Functions to add tanks, player tank, bullets, etc.
    std::vector<Shell*> getEnemyBullets();
    std::vector<Shell*> getPlayerBullets();
    std::vector<Tank*> getEnemyTanks();
    void AddTank(Tank* tank);
    void SetPlayerTank(Tank* playerTank);
    void AddBullet(Shell* bullet, bool isEnemy);
    void RemoveBullet(Shell *bullet, bool isEnemy);
    // Update function to update the game state
    void Update(float deltaTime);

private:
    // Container for tanks, player tank, bullets, etc.
    Tank *playerTank;
    std::vector<Tank*> enemyTanks;
    std::vector<Shell*> playerBullets;
    std::vector<Shell*> enemyBullets;
};