#pragma once

#include "header.h"
#include "Gallo.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "CaveGenerator.H"

EnemySpawner* EnemySpawner::pEnemySpawner = nullptr;

EnemySpawner* EnemySpawner::getInstance()
{
    if (pEnemySpawner == nullptr) {
        pEnemySpawner = new EnemySpawner();
    }
    return pEnemySpawner;
}

// constructor
EnemySpawner::EnemySpawner()
{
    for (size_t i = 0; i < m_iMaxGalloNumber; i++)
        gallos.push_back(new Gallo());
}

void EnemySpawner::spawnGallos() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();

    if (m_iLivingGalloNum < m_iMaxGalloNumber) { // check if have more Gallo to spawn
        if (m_iNextSpawnGalloTime < pEngine->getModifiedTime()) {
            m_iNextSpawnGalloTime = pEngine->getModifiedTime() + m_iGalloSpawnInterval;

            for (Gallo*& pGallo : gallos)
            {
                if (pGallo->getGalloState() == GalloState::GALLO_INACTIVE) {
                    pGallo->wakeUp(initGalloPosition());
                    ++m_iLivingGalloNum;
                    return;
                }

            }
            std::cout << "now have gallo number: " << m_iLivingGalloNum << std::endl;
        }
    }
}

Vec2 EnemySpawner::initGalloPosition() {
    Vec2 playerPosition = Player::getInstance()->getPosition();
    CaveGenerator* pCave = CaveGenerator::getInstance();

    int minX = playerPosition.x - m_iGalloSpawnOffset;
    int maxX = playerPosition.x + m_iGalloSpawnOffset;
    int minY = playerPosition.y - m_iGalloSpawnOffset;
    int maxY = playerPosition.y + m_iGalloSpawnOffset;

    Vec2 newPosition;
    while (1) {
        if (utils_rand(0, 1) == 0) { // fix x
            newPosition = { utils_rand(0, 1) == 0 ? minX : maxX, utils_rand(minY,maxY) };
        }
        else // fix y
        {
            newPosition = { utils_rand(minX,maxX), utils_rand(0, 1) == 0 ? minY : maxY };
        }

        int x = pCave->getMapXForScreenX(newPosition.x);
        int y = pCave->getMapYForScreenY(newPosition.y);
        if (pCave->isInBounds(x, y) && pCave->getMapValue(x, y) == cave_tile_spawner) {
            //std::cout << "new spawner pos: " << x << ",  " << y << std::endl;
            return newPosition;
        }
    }
}
