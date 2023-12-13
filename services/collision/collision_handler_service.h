#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "../../models/tank.h"
#include "../../models/buildings/barracks.h"
#include "../../models/components/shell.h"

class Tank;  // Forward declaration of Tank class
class Shell; // Forward declaration of Shell class

class CollisionHandlerService {
public:
    CollisionHandlerService();
    ~CollisionHandlerService();

    // Handle collision between two tanks
    void HandleTankTankCollision(Tank* tank1, Tank* tank2);

    // Handle collision between a tank and a shell
    void HandleTankShellCollision(Tank* tank, Shell* shell);

    void HandleTankBaracksCollision(Tank* tank, Barracks* barracks);

    void HandleShellBaracksCollision(Shell* shell, Barracks* barracks);


private:
    // Example function to check bounding box intersection
    bool BoundingBoxIntersect(Tank* tank, Tank* otherTank);

    // Example function to check bounding box intersection between a tank and a shell
    bool BoundingBoxIntersect(Tank* tank, Shell* shell);

    bool BoundingBoxIntersect(Tank* tank, Barracks* barracks); // New method
    bool BoundingBoxIntersect(Shell* shell, Barracks* barracks); // New method
};
