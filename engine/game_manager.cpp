#include "game_manager.h"

GameManager::GameManager() {
    collisionHandlerService = CollisionHandlerService();
    this->score = 0;
    this->timeLeft = 90.0f;
    this->gameFinished = false;
}

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

bool GameManager::isGameFinished() {
	return gameFinished;
}

void GameManager::AddTank(Tank* tank) {
	enemyTanks.push_back(tank);
}

void GameManager::AddBarracks(Barracks* barracks) {
	barracksList.push_back(barracks);
}

void GameManager::SetPlayerTank(Tank* playerTank) {
    this->playerTank = playerTank;
}

void GameManager::AddBullet(Shell* bullet, bool isEnemy) {
	if (isEnemy) {
		enemyBullets.push_back(bullet);
	}
	else {
		playerBullets.push_back(bullet);
	}
}

void GameManager::RemoveBullet(Shell* bullet, bool isEnemy) {
	if (isEnemy) {
		enemyBullets.erase(std::remove(enemyBullets.begin(), enemyBullets.end(), bullet),
						enemyBullets.end());
	}
	else {
		playerBullets.erase(std::remove(playerBullets.begin(), playerBullets.end(), bullet),
									playerBullets.end());
	}
}

void GameManager::RemoveDestroyedTanks() {
    for (auto& enemyTank : enemyTanks) {
        if (enemyTank->isDestroyed()) {
			/*enemyTanks.erase(std::remove(enemyTanks.begin(), enemyTanks.end(), enemyTank),
                							 enemyTanks.end());*/
            //enemyTank->setMovementState(RandomMovementService::MovementState::Stopped);
            if (!enemyTank->arePointsCounted()) {
				score += 100;
				enemyTank->setPointsCounted(true);
			}
		}
	}

    if (playerTank->isDestroyed() && !gameFinished) {
        //playerTank->setMovementState(RandomMovementService::MovementState::Stopped);
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

    // also for player's tank
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

// TODO: MOVE TANK MOVEMENT LOGIC FROM UPDATE(MAIN) IN THERE. SEE TODOs
void GameManager::Update(float deltaTime) {
    // Update time left
    timeLeft -= deltaTime;

    // if time is up, print the score
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

    // Update player tank
    //playerTank.Update(deltaTime);  // TODOOOO

    // Check and handle the player tank's position within the world boundaries
    glm::vec3& playerTankPosition = playerTank->getPosition();
    if (playerTankPosition.x < -MAP_SIZE_X || playerTankPosition.x > MAP_SIZE_X ||
        playerTankPosition.z < -MAP_SIZE_Z || playerTankPosition.z > MAP_SIZE_Z) {
        // Tank is attempting to leave the map, turn it back a little bit
        playerTankPosition.x = glm::clamp(playerTankPosition.x, -MAP_SIZE_X, MAP_SIZE_X);
        playerTankPosition.z = glm::clamp(playerTankPosition.z, -MAP_SIZE_Z, MAP_SIZE_Z);
        glm::vec3 newPosition = glm::vec3(playerTankPosition.x, playerTankPosition.y, playerTankPosition.z);
        playerTank->setPosition(newPosition);

    /*    playerTankPosition.x = 24.0f;
        playerTankPosition.z = 24.0f;*/

        // You may want to modify the tank's orientation here to give a turning-back effect
        // For example, adjust the tank's rotation angle or apply a force to simulate the turn.
    }

    // Update enemy tanks
    for (auto& enemyTank : enemyTanks) {
        //enemyTank->Update(deltaTime); // TODOOOO

        // Check and handle the enemy tank's position within the world boundaries
        glm::vec3& enemyTankPosition = enemyTank->getPosition();
        if (enemyTankPosition.x < -MAP_SIZE_X || enemyTankPosition.x > MAP_SIZE_X ||
            enemyTankPosition.z < -MAP_SIZE_Z || enemyTankPosition.z > MAP_SIZE_Z) {
            // Tank is attempting to leave the map, turn it back a little bit
            enemyTankPosition.x = glm::clamp(enemyTankPosition.x, -MAP_SIZE_X, MAP_SIZE_X);
            enemyTankPosition.z = glm::clamp(enemyTankPosition.z, -MAP_SIZE_Z, MAP_SIZE_Z);
            glm::vec3 newPosition = glm::vec3(enemyTankPosition.x, enemyTankPosition.y, enemyTankPosition.z);
            enemyTank->setPosition(newPosition);

            // You may want to modify the enemy tank's orientation here to give a turning-back effect
            // For example, adjust the tank's rotation angle or apply a force to simulate the turn.
        }

        if (enemyTank->isFollowingPlayer()) {
            enemyTank->setMovingState(false, 0);
            enemyTank->followPlayerWithTurret(playerTank);
        }

        if (enemyTank->getCurrentMovementState() != RandomMovementService::MovementState::FollowPlayerWithTurret) {
			enemyTank->setFollowingPlayer(false);
		}
    }

    // check for collisions between player tank and enemy tanks
    for (auto& enemyTank : enemyTanks) {
		collisionHandlerService.HandleTankTankCollision(playerTank, enemyTank);
	}

    // check for collisions between player tank and enemy bullets
    for (auto& enemyBullet : enemyBullets) {
		collisionHandlerService.HandleTankShellCollision(playerTank, enemyBullet);
	}

	// check for collisions between enemy tanks and player bullets
    for (auto& enemyTank : enemyTanks) {
        for (auto& playerBullet : playerBullets) {
			collisionHandlerService.HandleTankShellCollision(enemyTank, playerBullet);
		}

	}

    // check collisions with barracks
    for (auto& barracks : barracksList) {
		collisionHandlerService.HandleTankBaracksCollision(playerTank, barracks);

        // with enemy tanks
        for (auto& enemyTank : enemyTanks) {
            collisionHandlerService.HandleTankBaracksCollision(enemyTank, barracks);
        }

        // collision with bullets

        for (auto& playerBullet : playerBullets) {
			collisionHandlerService.HandleShellBaracksCollision(playerBullet, barracks);
		}

        for (auto& enemyBullet : enemyBullets) {
			collisionHandlerService.HandleShellBaracksCollision(enemyBullet, barracks);
		}
	}
    
	//// check for collisions between enemy tanks and enemy bullets
 //   for (auto& enemyTank : enemyTanks) {
 //       for (auto& enemyBullet : enemyBullets) {
	//		collisionHandlerService.HandleTankShellCollision(enemyTank, enemyBullet);
	//	}
	//}


    RemoveDestroyedTanks();
}
