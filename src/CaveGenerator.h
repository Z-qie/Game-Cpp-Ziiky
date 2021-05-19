#pragma once

#include <string>
#include <list>

#include "Zy21586TileManager.h"
#include "Room.h"
#include "Utils.h"

constexpr auto default_random_fill_percent = 50;//53, (50,5,128,72)is good now
constexpr auto wall_threshold_size = 50;
constexpr auto room_threshold_size = 50;

constexpr auto cave_tile_empty = 0;
constexpr auto cave_tile_wall = 1;
constexpr auto cave_tile_edge = 2;
constexpr auto cave_tile_spawner = 3;
constexpr auto cave_tile_rune = 4;


class Zy21586Engine;
class Room;
struct Vec2;
struct PosPair;

class CaveGenerator : public Zy21586TileManager
{
protected:
    explicit CaveGenerator(
        int caveWidth = 128,
        int caveHeight = 72,
        int tileSize = 40
    )
        : Zy21586TileManager(caveWidth, caveHeight, tileSize),
        randomFillPercent(default_random_fill_percent)
    {
        setTopLeftPositionOnScreen(0, 0);
    };

    static CaveGenerator* pCaveGenerator;

private:
  /*  std::string seedStr;
    bool useRandomSeed{ true };*/
    // the seed to generate cave
    unsigned int static seed;

    int passageSize{ 5 };
    int randomFillPercent{ default_random_fill_percent };
    int runeSetThreshold{ 300 };
    //int numOfRunes{ 0 };
    std::list<Room> m_oValidRooms;


public:


    static CaveGenerator* getInstance();
    virtual ~CaveGenerator() override { pCaveGenerator = nullptr; };
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX,
        int iMapY,
        int iStartPositionScreenX,
        int iStartPositionScreenY) const override;

    // generate cave map
    void generateCave();
    void randomFillMap();
    void smoothMap(int smoothStrength); // by cellular automata
    void refineMap(); // by flood algorithm 

    // classify tile types
    void setRuneTileType();
    void setOtherTileTypes();
    Vec2 initPlayerPosition();

    // delegating functions for generating cave map
    void getRegions(int tileType, std::list<std::list<Vec2>>& regions); // pass ref into func to make it efficient
    void getRegionTilesFrom(int startX, int startY, std::list<Vec2>& tiles);
    void connectClosestRooms(std::list<Room>& validRooms, bool forceAccessToMainRoom = false);
    void createPassage(Room* pRoomA, Room* pRoomB, Vec2 tileA, Vec2 tileB);
    int getSurroundingWallCount(int x, int y) const;
    bool isEdge(int x, int y)const;
    bool isSpawner(int x, int y) const;

    void static setSeed() {  seed = std::time(NULL); };
    unsigned int static getSeed() { return seed; };

};
