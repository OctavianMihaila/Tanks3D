#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "../../models/tank.h"
#include "../../models/buildings/barracks.h"
#include "../../models/components/shell.h"

class Tank;
class Shell;

class CollisionHandlerService {
public:
    CollisionHandlerService();
    ~CollisionHandlerService();

    void HandleTankTankCollision(Tank* tank1, Tank* tank2);
    void HandleTankShellCollision(Tank* tank, Shell* shell);
    void HandleTankBaracksCollision(Tank* tank, Barracks* barracks);
    void HandleShellBaracksCollision(Shell* shell, Barracks* barracks);

private:
    bool BoundingBoxIntersect(Tank* tank, Tank* otherTank);
    bool BoundingBoxIntersect(Tank* tank, Shell* shell);
    bool BoundingBoxIntersect(Tank* tank, Barracks* barracks);
    bool BoundingBoxIntersect(Shell* shell, Barracks* barracks);
};
