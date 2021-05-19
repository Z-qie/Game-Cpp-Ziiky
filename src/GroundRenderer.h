#pragma once

#include <string>
#include <list>

#include "Zy21586TileManager.h"
#include "Room.h"
#include "Utils.h"


constexpr auto ground_tile_00 = 0;
constexpr auto ground_tile_01 = 1;
constexpr auto ground_tile_02 = 2;
constexpr auto ground_tile_03 = 3;
constexpr auto ground_tile_04 = 4;
constexpr auto ground_tile_05 = 5;


class Zy21586Engine;
struct Vec2;

class GroundRenderer : public Zy21586TileManager
{
protected:
    explicit GroundRenderer(
        int caveWidth = 128,
        int caveHeight = 72,
        int tileSize = 40
    );

    static GroundRenderer* pGroundRenderer;

private:
    SimpleImage groundTileSprites[5];


public:
    static GroundRenderer* getInstance();
    virtual ~GroundRenderer() override { pGroundRenderer = nullptr; };
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX,
        int iMapY,
        int iStartPositionScreenX,
        int iStartPositionScreenY) const override;

    // generate cave map
    void randomFillSprite();
};
