#pragma once

#include <vector>
#include <memory>
#include "Zy21586TileManager.h"
#include "DeadWallUnit.h"


constexpr auto dead_wall_empty = 0;
constexpr auto dead_wall_wall = 1;
constexpr auto dead_wall_edge = 2;
//constexpr auto dead_wall_attack = 3;

class DeadWallSpawner : public Zy21586TileManager
{
public:
    int m_iNextIdleUpdateTime{ 0 };
    int m_iIdleUpdateInterval{ 300 };

    int m_iNextAttackUpdateTime{ 0 };
    int m_iAttackUpdateInterval{ 100 };

    mutable int m_iCurrentDeadWallIndex{ 0 };
    std::vector<std::shared_ptr<DeadWallUnit>> m_oDeadWalls;

protected:
    explicit DeadWallSpawner(
        int mapWidth = 128 * 5,
        int mapHeight = 72 * 5,
        int tileSize = 8
    )
        : Zy21586TileManager(mapWidth, mapHeight, tileSize)
    {
        setTopLeftPositionOnScreen(0, 0);
    };

    static DeadWallSpawner* pDeadWallSpawner;

public:
    static DeadWallSpawner* getInstance();

    virtual ~DeadWallSpawner() override {
        pDeadWallSpawner = nullptr;
    };

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX,
        int iMapY,
        int iStartPositionScreenX,
        int iStartPositionScreenY) const override;

    void generateCreature();
    void updateDeadWall();

    //std::shared_ptr<DeadWallUnit> getDeadWallUnitAt(int x, int y) {
    //    return vector[];
    //}

};
