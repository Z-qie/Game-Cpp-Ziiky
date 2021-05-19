#pragma once

#include "UtilCollisionDetection.h"

class CollisionSystem : public CollisionDetection
{
public:
    static bool checkObstacleBySquare(int centerX, int centerY, int iSide);
    //static bool checkObstacleByTranslation(int centerX, int centerY);
};

