#pragma once

#include <vector>

#include "header.h"
#include "DeadWallSpawner.h"
#include "CollisionSystem.h"
#include "CaveGenerator.h"
#include "Zy21586Engine.h"
#include "Player.h"
#include "Utils.h"

DeadWallSpawner* DeadWallSpawner::pDeadWallSpawner = nullptr;
DeadWallSpawner* DeadWallSpawner::getInstance() {
    if (pDeadWallSpawner == nullptr) {
        pDeadWallSpawner = new DeadWallSpawner();
    }
    return pDeadWallSpawner;
}

void DeadWallSpawner::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX,
    int iMapY,
    int iStartPositionScreenX,
    int iStartPositionScreenY) const {

    if (getMapValue(iMapX, iMapY) == dead_wall_edge) {
        std::shared_ptr<DeadWallUnit> thisDeadWallUnit = m_oDeadWalls[m_iCurrentDeadWallIndex];

        // check if player is close to dead wall
        Player* pPlayer = Player::getInstance();
        thisDeadWallUnit->foundPlayer =
            CollisionSystem::checkCircles(
                iStartPositionScreenX, iStartPositionScreenY,
                pPlayer->getPosition().x, pPlayer->getPosition().y,
                DeadWallUnit::iAttackDetectionRadius)
            ? true : false;

        // calculate next attack position
        Vec2 attackPosition = thisDeadWallUnit->getAttackPosition(iStartPositionScreenX, iStartPositionScreenY);
        // render
        pSurface->drawLine(
            iStartPositionScreenX, iStartPositionScreenY,
            attackPosition.x, attackPosition.y,
            thisDeadWallUnit->m_iColor);

        pSurface->drawOval(attackPosition.x - 2, attackPosition.y - 2, attackPosition.x + 2, attackPosition.y + 2, thisDeadWallUnit->m_iColor);


        if (++m_iCurrentDeadWallIndex >= m_oDeadWalls.size()) {
            //std::cout << m_iCurrentDeadWallIndex << ": " << m_oDeadWalls.size() << std::endl;
            m_iCurrentDeadWallIndex = 0;
        }
    }
}

void DeadWallSpawner::updateDeadWall() {
    int iCurrentTime = Zy21586Engine::getInstance()->getModifiedTime();

    if (m_iNextIdleUpdateTime < iCurrentTime) {
        m_iNextIdleUpdateTime = iCurrentTime + m_iIdleUpdateInterval;
        DeadWallUnit::canChangeIdlePosition = true;
        DeadWallUnit::isPlayerTakingHit = false; // lazy........using m_iIdleUpdateInterval instead
    }
    else
    {
        DeadWallUnit::canChangeIdlePosition = false;
    }

    if (m_iNextAttackUpdateTime < iCurrentTime) {
        m_iNextAttackUpdateTime = iCurrentTime + m_iAttackUpdateInterval;
        DeadWallUnit::canChangeAttackPosition = true;
    }
    else
    {
        DeadWallUnit::canChangeAttackPosition = false;
    }
}

void DeadWallSpawner::generateCreature() {
    CaveGenerator* pCave = CaveGenerator::getInstance();
    for (int x = 0; x < m_iMapWidth; x++)
        for (int y = 0; y < m_iMapHeight; y++) {
            int CaveTileX = x / 5;
            int CaveTileY = y / 5;

            // using unique pointer here
            if (setMapValue(x, y, pCave->getMapValue(CaveTileX, CaveTileY)) == dead_wall_edge) {
                auto newDeadWallUnit = std::make_shared<DeadWallUnit>();

                if (pCave->isInBounds(CaveTileX, CaveTileY - 1) && pCave->getMapValue(CaveTileX, CaveTileY - 1) == cave_tile_empty)  // top
                    newDeadWallUnit->isTopEmpty = true;

                if (pCave->isInBounds(CaveTileX, CaveTileY + 1) && pCave->getMapValue(CaveTileX, CaveTileY + 1) == cave_tile_empty) // bottom
                    newDeadWallUnit->isBottomEmpty = true;

                if (pCave->isInBounds(CaveTileX - 1, CaveTileY) && pCave->getMapValue(CaveTileX - 1, CaveTileY) == cave_tile_empty) // left
                    newDeadWallUnit->isLeftEmpty = true;

                if (pCave->isInBounds(CaveTileX + 1, CaveTileY) && pCave->getMapValue(CaveTileX + 1, CaveTileY) == cave_tile_empty) // right
                    newDeadWallUnit->isRightEmpty = true;

                m_oDeadWalls.push_back(newDeadWallUnit);
            }
        }
}
