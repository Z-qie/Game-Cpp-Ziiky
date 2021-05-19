#pragma once

#include <list>

#include "header.h"
#include "Room.h"
#include "Utils.h"
#include "CaveGenerator.h"

Room::Room()
    : roomSize(0)
    , id(0)
{};

Room::Room(std::list<Vec2> roomTiles, const CaveGenerator* pCaveMap, unsigned int id)
    : tiles(roomTiles)
    , roomSize(roomTiles.size())
    , id(id)
{
    for each (const Vec2 & tile in tiles) {
        for (int x = tile.x - 1; x <= tile.x + 1; x++) {
            for (int y = tile.y - 1; y <= tile.y + 1; y++) {
                if (x == tile.x || y == tile.y) {
                    if (pCaveMap->getMapValue(x, y) == cave_tile_wall) {
                        edgeTiles.push_back(tile);
                    }
                }
            }
        }
    }
}

void Room::connectRooms(Room& roomA, Room& roomB) {
    if (roomA.isAccessibleToMainRoom)
        roomB.setAccessToMainRoom();
    else if (roomB.isAccessibleToMainRoom)
        roomA.setAccessToMainRoom();

    roomA.connectedRooms.push_back(roomB);
    roomB.connectedRooms.push_back(roomA);
}

void Room::setAccessToMainRoom() {
    if (!isAccessibleToMainRoom) {
        isAccessibleToMainRoom = true;
        // set all connected rooms as accessiable to main room as well
        for (Room& connectedRoom : connectedRooms) 
            connectedRoom.setAccessToMainRoom();
    }
}

bool Room::isConnected(const Room& otherRoom) const {
    //return utils_contains(connectedRooms, otherRoom);
    auto it = std::find(connectedRooms.begin(), connectedRooms.end(), otherRoom);
    return it != connectedRooms.end();
}

bool Room::operator==(const Room& otherRoom) const
{
    return (this->id == otherRoom.id) ? true : false;
}