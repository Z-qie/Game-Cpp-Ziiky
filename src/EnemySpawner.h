#pragma once
#include <vector>
#include "Utils.h"

class Gallo;

class EnemySpawner
{
private:
    const int m_iMaxGalloNumber{ 25 };
    const int m_iGalloSpawnInterval{ 700 };
    const int m_iGalloSpawnOffset{ 400 };

    std::vector<Gallo*> gallos;

    int m_iLivingGalloNum{ 0 };
    int m_iNextSpawnGalloTime{ 0 };

protected:
    EnemySpawner();
    static EnemySpawner* pEnemySpawner;

public:
    static EnemySpawner* getInstance();
    ~EnemySpawner() { pEnemySpawner = nullptr; };

    int getLivingGalloNum()const { return m_iLivingGalloNum; };
    void decrementLivingGallo() { --m_iLivingGalloNum; };
    const std::vector<Gallo*>& getGallos() { return gallos; };
    void EnemySpawner::spawnGallos();
    Vec2 EnemySpawner::initGalloPosition();
};

