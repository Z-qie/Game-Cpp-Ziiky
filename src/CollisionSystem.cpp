#pragma once    

#include "header.h"
#include "CollisionSystem.h"
#include "UtilCollisionDetection.h"
#include "Utils.h"
#include "Zy21586Engine.h"
#include "CaveGenerator.h"


bool CollisionSystem::checkObstacleBySquare(int centerX, int centerY, int iSide) {
    int iLeftX = centerX - iSide;
    int iRightX = centerX + iSide;
    int iTopY = centerY - iSide;
    int iBottomY = centerY + iSide;

    CaveGenerator* pCave = CaveGenerator::getInstance();

    //no need to check boundary because size is big enough
    int x = 0;
    int y = 0;
    int tileType = 0;
    // check top-left
    x = pCave->getMapXForScreenX(iLeftX);
    y = pCave->getMapYForScreenY(iTopY);
    if (!pCave->isInBounds(x, y))
        return true;

    tileType = pCave->getMapValue(x, y);
    if (tileType != cave_tile_empty && tileType != cave_tile_spawner)
        return true;

    // check bottom-left
    x = pCave->getMapXForScreenX(iLeftX);
    y = pCave->getMapYForScreenY(iBottomY);
    if (!pCave->isInBounds(x, y))
        return true;

    tileType = pCave->getMapValue(x, y);
    if (tileType != cave_tile_empty && tileType != cave_tile_spawner)
        return true;

    // check top-right
    x = pCave->getMapXForScreenX(iRightX);
    y = pCave->getMapYForScreenY(iTopY);
    if (!pCave->isInBounds(x, y))
        return true;

    tileType = pCave->getMapValue(x, y);
    if (tileType != cave_tile_empty && tileType != cave_tile_spawner)
        return true;

    // check bottom-right
    x = pCave->getMapXForScreenX(iRightX);
    y = pCave->getMapYForScreenY(iBottomY);
    if (!pCave->isInBounds(x, y))
        return true;

    tileType = pCave->getMapValue(x, y);
    if (tileType != cave_tile_empty && tileType != cave_tile_spawner)
        return true;

    return false;
}
