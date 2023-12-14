#include "collision_handler_service.h"  // Include the header file for the CollisionHandlerService class

CollisionHandlerService::CollisionHandlerService() {
    // Constructor implementation
}

CollisionHandlerService::~CollisionHandlerService() {
    // Destructor implementation
}

void CollisionHandlerService::HandleTankTankCollision(Tank* tank1, Tank* tank2) {
    if (BoundingBoxIntersect(tank1, tank2)) {

        glm::vec3 newDistanceBetweenTanks = glm::vec3(0.7f, 0.0f, 0.7f);

        glm::vec3 tank1Position = tank1->getPosition();
        glm::vec3 tank2Position = tank2->getPosition();

        glm::vec3 tank1Direction = glm::normalize(tank1Position - tank2Position);
        glm::vec3 tank2Direction = glm::normalize(tank2Position - tank1Position);

        tank1Position += tank1Direction * newDistanceBetweenTanks;
        tank2Position += tank2Direction * newDistanceBetweenTanks;

        tank1->setPosition(tank1Position);
        tank2->setPosition(tank2Position);
    }
}

void CollisionHandlerService::HandleTankShellCollision(Tank* tank, Shell* shell) {
    if (BoundingBoxIntersect(tank, shell)) {
        if (shell->isEnemy() != tank->isEnemy()) {
            tank->setDamagedComponents((int)tank->getHp());
			tank->deacreaseHp(35);
			shell->setHasCollided(true);
		}
    }
}

void CollisionHandlerService::HandleTankBaracksCollision(Tank* tank, Barracks* barracks) {
    if (BoundingBoxIntersect(tank, barracks)) {
        
        // only the tank should be stopped
        glm::vec3 tankPosition = tank->getPosition();
        glm::vec3 barracksPosition = barracks->getPosition();

        glm::vec3 tankDirection = glm::normalize(tankPosition - barracksPosition);
		tankPosition += tankDirection * 0.1f;
		tank->setPosition(tankPosition);

    }
}

void CollisionHandlerService::HandleShellBaracksCollision(Shell* shell, Barracks* barracks) {
    if (BoundingBoxIntersect(shell, barracks)) {
        // Handle the collision, e.g., decrease the baracks's health or destroy the shell
        shell->setHasCollided(true);
    }
}

bool CollisionHandlerService::BoundingBoxIntersect(Tank* tank, Barracks* barracks) {
    glm::vec3 tankMin = tank->getPosition() - tank->getBoundingBoxSize() / 2.0f;
    glm::vec3 tankMax = tank->getPosition() + tank->getBoundingBoxSize() / 2.0f;

    glm::vec3 barracksMin = barracks->getPosition() - barracks->getBoundingBoxSize() / 2.0f;
    glm::vec3 barracksMax = barracks->getPosition() + barracks->getBoundingBoxSize() / 2.0f;

    // Check for intersection
    if (tankMin.x < barracksMax.x && tankMax.x > barracksMin.x &&
        tankMin.y < barracksMax.y && tankMax.y > barracksMin.y &&
        tankMin.z < barracksMax.z && tankMax.z > barracksMin.z) {
        return true;
    }

    return false;
}

bool CollisionHandlerService::BoundingBoxIntersect(Shell* shell, Barracks* barracks) {
    // Offset that prevent the shell from despawn when going very close to the building.
    glm::vec3 buildingOffset = glm::vec3(0.8f, 0.0f, 0.8f); 
    glm::vec3 shellMin = shell->getPosition() - (shell->getBoundingBoxSize() - buildingOffset) / 2.0f;
    glm::vec3 shellMax = shell->getPosition() + (shell->getBoundingBoxSize()  - buildingOffset) / 2.0f;

    glm::vec3 barracksMin = barracks->getPosition() - (barracks->getBoundingBoxSize() - buildingOffset) / 2.0f;
    glm::vec3 barracksMax = barracks->getPosition() + (barracks->getBoundingBoxSize() - buildingOffset) / 2.0f;

    // Check for intersection
    if (shellMin.x < barracksMax.x && shellMax.x > barracksMin.x &&
        shellMin.y < barracksMax.y && shellMax.y > barracksMin.y &&
        shellMin.z < barracksMax.z && shellMax.z > barracksMin.z) {
        return true;
    }

    return false;
}


bool CollisionHandlerService::BoundingBoxIntersect(Tank* tank, Tank* otherTank) {

    glm::vec3 tankMin = tank->getPosition() - tank->getBoundingBoxSize() / 2.0f;
    glm::vec3 tankMax = tank->getPosition() + tank->getBoundingBoxSize() / 2.0f;


    glm::vec3 otherTankMin = otherTank->getPosition() - otherTank->getBoundingBoxSize() / 2.0f;
    glm::vec3 otherTankMax = otherTank->getPosition() + otherTank->getBoundingBoxSize() / 2.0f;

    // Check for intersection
    if (tankMin.x < otherTankMax.x && tankMax.x > otherTankMin.x &&
        tankMin.y < otherTankMax.y && tankMax.y > otherTankMin.y &&
        tankMin.z < otherTankMax.z && tankMax.z > otherTankMin.z) {
        return true;  // Bounding boxes intersect
    }

    return false;  // Placeholder: Bounding boxes do not intersect
}

bool CollisionHandlerService::BoundingBoxIntersect(Tank* tank, Shell* shell) {
    glm::vec3 tankMin = tank->getPosition() - tank->getBoundingBoxSize() / 2.0f;
    glm::vec3 tankMax = tank->getPosition() + tank->getBoundingBoxSize() / 2.0f;

    glm::vec3 shellMin = shell->getPosition() - shell->getBoundingBoxSize() / 2.0f;
    glm::vec3 shellMax = shell->getPosition() + shell->getBoundingBoxSize() / 2.0f;

    // Check for intersection
    if (tankMin.x < shellMax.x && tankMax.x > shellMin.x &&
        tankMin.y < shellMax.y && tankMax.y > shellMin.y &&
        tankMin.z < shellMax.z && tankMax.z > shellMin.z) {
		return true;
	}

    return false;
}
