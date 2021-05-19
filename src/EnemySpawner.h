#pragma once
#include <vector>
#include "Utils.h"

class Gallo;

//All gallos are controlled by EnemySpawner.
//1. the max number of gallos alive in the game: 25 max
//2. the interval of spawning is 0.8s
//3. the position of each gallo spawned: 400 radius from player(outside the camera's view), 
//to give the player a feeling that the enemies are already there.
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

