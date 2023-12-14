#pragma once

#include <vector>
#include "../models/tank.h"
#include "../models/components/shell.h"
#include "../models/buildings/barracks.h"
#include "../services/collision/collision_handler_service.h"
#include <unordered_map>

#define MAP_SIZE_X 25.0f
#define MAP_SIZE_Z 25.0f

class GameManager {
public:
    GameManager(std::unordered_map<std::string, Mesh*> meshes);
    GameManager();

    Tank *getPlayerTank();
    std::vector<Shell*> getEnemyBullets();
    std::vector<Shell*> getPlayerBullets();
    std::vector<Tank*> getEnemyTanks();
    std::vector<Barracks*> getBarracksList();
    bool isGameFinished();
    bool CheckPositionIsEmpty(glm::vec3 position, float areaX, float areaZ);
    void AddTank(Tank* tank);
    void AddBullet(Shell* bullet, bool isEnemy);
    void AddBarracks(Barracks* barracks);
    void SetPlayerTank(Tank* playerTank);
    void RemoveBullet(Shell* bullet);
    void RemoveBullet(Shell *bullet, bool isEnemy);
    void RemoveDestroyedTanks();
    void Update(float deltaTime);

private:
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