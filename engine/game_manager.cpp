#include "game_manager.h"

GameManager::GameManager(std::unordered_map<std::string, Mesh*> meshes) {
    this->collisionHandlerService = CollisionHandlerService();
    this->score = 0;
    this->timeLeft = 90.0f;
    this->gameFinished = false;

    Chassis chassis = Chassis(glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.1, 0.1, 0.05));
    Cannon cannon = Cannon(meshes["cannon"], glm::vec3(0.5, 0.5, 0.5));
    Turret turret = Turret(meshes["turret"], glm::vec3(0.3, 0.15, 0));
    this->playerTank = new Tank(chassis, turret, cannon, false, glm::vec3(0.2, 0.2, 0.2));
}

GameManager::GameManager() {}

std::vector<Shell*> GameManager::getEnemyBullets() {
	return enemyBullets;
}

std::vector<Shell*> GameManager::getPlayerBullets() {
	return playerBullets;
}

std::vector<Tank*> GameManager::getEnemyTanks() {
	return enemyTanks;
}

std::vector<Barracks*> GameManager::getBarracksList() {
	return barracksList;
}

Tank* GameManager::getPlayerTank() {
	return playerTank;
}

bool GameManager::isGameFinished() {
	return gameFinished;
}

void GameManager::AddTank(Tank* tank) {
	enemyTanks.push_back(tank);
}

void GameManager::AddBarracks(Barracks* barracks) {
	barracksList.push_back(barracks);
}

void GameManager::AddBullet(Shell* bullet, bool isEnemy) {
    if (isEnemy) {
        enemyBullets.push_back(bullet);
    }
    else {
        playerBullets.push_back(bullet);
    }
}

void GameManager::SetPlayerTank(Tank* playerTank) {
    this->playerTank = playerTank;
}

void GameManager::RemoveBullet(Shell* bullet, bool isEnemy) {
	if (isEnemy) {
		enemyBullets.erase(std::remove(enemyBullets.begin(), enemyBullets.end(), bullet),
						enemyBullets.end());
	} else {
		playerBullets.erase(std::remove(playerBullets.begin(), playerBullets.end(), bullet),
									playerBullets.end());
	}
}

void GameManager::RemoveDestroyedTanks() {
    for (auto& enemyTank : enemyTanks) {
        if (enemyTank->isDestroyed()) {
            if (!enemyTank->arePointsCounted()) {
				score += 100;
				enemyTank->setPointsCounted(true);
			}
		}
	}

    if (playerTank->isDestroyed() && !gameFinished) {
        std::cout << "GAME OVER. YOU LOST !" << std::endl;
        gameFinished = true;
	}
}

void GameManager::RemoveBullet(Shell* bullet) {
	playerBullets.erase(std::remove(playerBullets.begin(), playerBullets.end(), bullet),
        						playerBullets.end());
}

bool GameManager::CheckPositionIsEmpty(glm::vec3 position, float areaX, float areaZ) {
    for (auto& enemyTank : enemyTanks) {
        glm::vec3 enemyTankPos = enemyTank->getPosition();
        if (std::abs(enemyTankPos.x - position.x) < areaX && std::abs(enemyTankPos.z - position.z) < areaZ) {
            return false;
        }
    }

    for (auto& barracks : barracksList) {
        glm::vec3 barracksPos = barracks->getPosition();
        if (std::abs(barracksPos.x - position.x) < areaX && std::abs(barracksPos.z - position.z) < areaZ) {
            return false;
        }
    }

    if (playerTank != nullptr) {
        glm::vec3 playerTankPos = playerTank->getPosition();
        if (std::abs(playerTankPos.x - position.x) < areaX && std::abs(playerTankPos.z - position.z) < areaZ) {
            return false;
        }
    }

    return true;
}

bool CheckIfAllEnemiesAreDestroyed(std::vector<Tank*> enemyTanks) {
	for (auto& enemyTank : enemyTanks) {
		if (!enemyTank->isDestroyed()) {
			return false;
		}
	}

	return true;
}

void GameManager::Update(float deltaTime) {
    timeLeft -= deltaTime;
    playerTank->deacreaseCooldown(deltaTime);

    // If time is up, print the score.
    if (timeLeft <= 0 && !gameFinished) {
		std::cout << "GAME OVER. YOU WON !" << std::endl;
		std::cout << "Score: " << score << std::endl;

        gameFinished = true;
	}

    if (CheckIfAllEnemiesAreDestroyed(enemyTanks) && !gameFinished) {
        std::cout << "GAME OVER. YOU WON !" << std::endl;
        int bonusPoints = (int)timeLeft * 10;
        std::cout << "Score: " << score + bonusPoints << std::endl;

		gameFinished = true;
    }

    // Check and handle the player tank's position within the world boundaries.
    glm::vec3& playerTankPosition = playerTank->getPosition();

    if (playerTankPosition.x < -MAP_SIZE_X || playerTankPosition.x > MAP_SIZE_X ||
        playerTankPosition.z < -MAP_SIZE_Z || playerTankPosition.z > MAP_SIZE_Z) {
        // Tank is attempting to leave the map, turn it back a little bit.
        playerTankPosition.x = glm::clamp(playerTankPosition.x, -MAP_SIZE_X, MAP_SIZE_X);
        playerTankPosition.z = glm::clamp(playerTankPosition.z, -MAP_SIZE_Z, MAP_SIZE_Z);
        glm::vec3 newPosition = glm::vec3(playerTankPosition.x, playerTankPosition.y, playerTankPosition.z);
        playerTank->setPosition(newPosition);

        playerTankPosition.z = 24.0f;
    }

    // Update enemy tanks.
    for (auto& enemyTank : enemyTanks) {
        glm::vec3& enemyTankPosition = enemyTank->getPosition();

        // Check and handle the enemy tank's position within the world boundaries
        if (enemyTankPosition.x < -MAP_SIZE_X || enemyTankPosition.x > MAP_SIZE_X ||
            enemyTankPosition.z < -MAP_SIZE_Z || enemyTankPosition.z > MAP_SIZE_Z) {
            // Tank is attempting to leave the map, turn it back a little bit
            enemyTankPosition.x = glm::clamp(enemyTankPosition.x, -MAP_SIZE_X, MAP_SIZE_X);
            enemyTankPosition.z = glm::clamp(enemyTankPosition.z, -MAP_SIZE_Z, MAP_SIZE_Z);
            glm::vec3 newPosition = glm::vec3(enemyTankPosition.x, enemyTankPosition.y, enemyTankPosition.z);
            enemyTank->setPosition(newPosition);
        }

        if (enemyTank->isFollowingPlayer()) {
            enemyTank->setMovingState(false, 0);
            enemyTank->followPlayerWithTurret(playerTank);
        }

        if (enemyTank->getCurrentMovementState() != RandomMovementService::MovementState::FollowPlayerWithTurret) {
			enemyTank->setFollowingPlayer(false);
		}
    }

    // Collision detection and handling.

    for (auto& enemyTank : enemyTanks) {
		collisionHandlerService.HandleTankTankCollision(playerTank, enemyTank);
	}

    for (auto& enemyBullet : enemyBullets) {
		collisionHandlerService.HandleTankShellCollision(playerTank, enemyBullet);
	}

    for (auto& enemyTank : enemyTanks) {
        for (auto& playerBullet : playerBullets) {
			collisionHandlerService.HandleTankShellCollision(enemyTank, playerBullet);
		}

	}

    for (auto& barracks : barracksList) {
		collisionHandlerService.HandleTankBaracksCollision(playerTank, barracks);

        for (auto& enemyTank : enemyTanks) {
            collisionHandlerService.HandleTankBaracksCollision(enemyTank, barracks);
        }

        for (auto& playerBullet : playerBullets) {
			collisionHandlerService.HandleShellBaracksCollision(playerBullet, barracks);
		}

        for (auto& enemyBullet : enemyBullets) {
			collisionHandlerService.HandleShellBaracksCollision(enemyBullet, barracks);
		}
	}
    
    RemoveDestroyedTanks();
}
