#pragma once

#include <string>
#include <list>

#include "TileManager.h"
#include "Utils.h"

class Zy21586Engine;
class TileManager;
struct Vec2;
struct PosPair;

class Zy21586TileManager : public TileManager
{
public:
    // default constructor
    Zy21586TileManager()
        :TileManager(0, 0)
    {};
    // constructor
    Zy21586TileManager(
        int iWidth,
        int iHeight,
        int tileSize
    )
        : TileManager(tileSize, tileSize, iWidth, iHeight)
    {};

    Zy21586TileManager(
        int iWidth,
        int iHeight,
        int tileHeight,
        int tileWidth
    )
        : TileManager(tileHeight, tileWidth, iWidth, iHeight)
    {};

    virtual ~Zy21586TileManager() override {};


    //int getSurroundingWallCount(int x, int y) const;
    virtual bool isInBounds(int x, int y) const;
    virtual bool isEmpty(int x, int y) const;
    virtual void drawCircle(Vec2 point, int radius, int value);
    std::list<Vec2> computeLine(Vec2 from, Vec2 to);


};
