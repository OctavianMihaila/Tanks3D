#include "game_manager.h"

GameManager::GameManager() {
    // Initialize your board manager
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

void GameManager::AddTank(Tank* tank) {
	enemyTanks.push_back(tank);
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

// TODO: MOVE TANK MOVEMENT LOGIC FROM UPDATE(MAIN) IN THERE. SEE TODOs
void GameManager::Update(float deltaTime) {
    

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
            std::cout << "tank is following player\n" << std::endl;
            enemyTank->setMovingState(false, 0);
            enemyTank->followPlayerWithTurret(playerTank);
        }

        if (enemyTank->getCurrentMovementState() != RandomMovementService::MovementState::FollowPlayerWithTurret) {
			enemyTank->setFollowingPlayer(false);
		}
    }

}
