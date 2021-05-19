#pragma once

#include <list>
#include "CaveGenerator.h"
#include "Utils.h"

class CaveGenerator;

class Room
{
public:
    Room();
    Room(std::list<Vec2> roomTiles, const CaveGenerator* pCaveMap, unsigned int id);
    void setAccessToMainRoom();
    bool isConnected(const Room& otherRoom) const;
    bool operator==(const Room& otherRoom) const;
    static void connectRooms(Room & roomA, Room & roomB);

public:
    std::list<Vec2> tiles;
    std::list<Vec2> edgeTiles;
    std::list<Room> connectedRooms;
    int roomSize{ 0 }; // tile number
    unsigned int id{ 0 };
    bool isMainRoom{ false };
    bool isAccessibleToMainRoom{ false };
};


struct RoomComparator
{
    // Compare 2 Room objects using name
    bool operator ()(const Room& roomA, const Room& roomB)
    {
        if (roomA.roomSize == roomB.roomSize)
            return roomA.id < roomB.id; // if sizes are equal, check id.
        return roomA.roomSize < roomA.roomSize;
    }
};