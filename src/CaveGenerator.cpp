#pragma once

#include <string>
#include <list>
#include <queue>
#include <math.h>
#include <iterator>
#include <algorithm>
#include "header.h"
#include "TileManager.h"
#include "Utils.h"
#include "CaveGenerator.h"
#include "Room.h"
#include "Zy21586Engine.h"
#include "RuneManager.h"
#include "SimpleImage.h"
#include "ImagePixelMapping.h"

CaveGenerator* CaveGenerator::pCaveGenerator = nullptr;
unsigned int CaveGenerator::seed = 0;

CaveGenerator* CaveGenerator::getInstance()
{
	if (pCaveGenerator == nullptr) {
		pCaveGenerator = new CaveGenerator();
	}
	return pCaveGenerator;
};

void CaveGenerator::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX,
	int iMapY,
	int iStartPositionScreenX,
	int iStartPositionScreenY) const {

	switch (getMapValue(iMapX, iMapY))
	{
	case cave_tile_empty:
	case cave_tile_spawner:
		break;

	case cave_tile_wall:
		pSurface->drawRectangle(
			iStartPositionScreenX,	// Left
			iStartPositionScreenY,	// Top
			iStartPositionScreenX + getTileWidth() - 1,		// Right
			iStartPositionScreenY + getTileHeight() - 1,	// Bottom
			0x151515);	// Pixel colour

		break;
	case cave_tile_edge: {
		if (utils_rand(0, 100) < 40) {
			pSurface->drawRectangle(
				iStartPositionScreenX + utils_rand(-3, 3),	// Left
				iStartPositionScreenY + utils_rand(-3, 3),	// Top
				iStartPositionScreenX + getTileWidth() - 1 + utils_rand(-3, 3),		// Right
				iStartPositionScreenY + getTileHeight() - 1 + utils_rand(-3, 3),	// Bottom
				0x151515);	// Pixel colour
		}
		else {
			pSurface->drawRectangle(
				iStartPositionScreenX,	// Left
				iStartPositionScreenY,	// Top
				iStartPositionScreenX + getTileWidth() - 1,		// Right
				iStartPositionScreenY + getTileHeight() - 1,	// Bottom
				0x151515);	// Pixel colour
		}
		break;
	}
	default:
		break;
	}
}

void CaveGenerator::generateCave() {
	randomFillMap();
	smoothMap(5);
	refineMap();
	setRuneTileType();
	connectClosestRooms(m_oValidRooms);
	setOtherTileTypes();
}

void CaveGenerator::randomFillMap() {
	// select seed
	//srand(useRandomSeed ? time(NULL) : std::hash<std::string>()(seedStr));
	//srand(time(NULL));
	std::srand(seed);
	for (int x = 0; x < m_iMapWidth; x++)
		for (int y = 0; y < m_iMapHeight; y++)
			// set board as wall
			if (x == 0 || x == m_iMapWidth - 1 || y == 0 || y == m_iMapHeight - 1)
				setMapValue(x, y, cave_tile_wall);
			else // random choose wall
				setMapValue(x, y,
					(utils_rand(0, 100) < randomFillPercent) ?
					cave_tile_wall : cave_tile_empty);
}

void CaveGenerator::smoothMap(int smoothStrength) {
	for (int i = 0; i < smoothStrength; i++)
		for (int x = 0; x < m_iMapWidth; x++) {
			for (int y = 0; y < m_iMapHeight; y++) {
				int neighbourWallTiles = getSurroundingWallCount(x, y);
				if (neighbourWallTiles > 4)
					setMapValue(x, y, cave_tile_wall);
				else if (neighbourWallTiles < 4) // cannot make it equal to 4
					setMapValue(x, y, cave_tile_empty);
			}
		}
}

void CaveGenerator::refineMap() {

	std::list<std::list<Vec2>> wallRegions;
	getRegions(cave_tile_wall, wallRegions); // 1=wall at this point

	// destroy all wall region which is smaller than threshold
	for (const std::list<Vec2>& wallRegion : wallRegions)
		if (wallRegion.size() < wall_threshold_size) {
			for (const Vec2& Position : wallRegion)
				setMapValue(Position.x, Position.y, cave_tile_empty);
		}

	// destroy all room region which is smaller than threshold
	std::list<std::list<Vec2>> roomRegions;
	getRegions(cave_tile_empty, roomRegions); // 0=room at this point

	unsigned int roomId = 0; // initialize room id as 0

	// valid rooms after refining on stack
	for (const std::list<Vec2>& roomRegion : roomRegions) {
		if (roomRegion.size() < room_threshold_size) {
			for (const Vec2& Position : roomRegion)
				setMapValue(Position.x, Position.y, cave_tile_wall);
		}
		else {
			m_oValidRooms.push_back(Room(roomRegion, this, roomId++));
		}
	}

	// connect all regions together
	m_oValidRooms.sort(RoomComparator()); // sort assendingly by room size

	////test
	//std::cout << m_oValidRooms.front().roomSize << std::endl;
	//std::cout << m_oValidRooms.back().roomSize << std::endl;

	// set the smallest one as main room
	m_oValidRooms.back().isMainRoom = true;
	m_oValidRooms.back().isAccessibleToMainRoom = true;
	
}

void CaveGenerator::setRuneTileType() {
	//std::cout << m_oValidRooms.size() << std::endl;

	for (const Room& room : m_oValidRooms) {
		int iNumOfRunes = room.roomSize / runeSetThreshold; // set num of rune based on size of each room
		iNumOfRunes = iNumOfRunes == 0 ? 1 : iNumOfRunes; // make sure each room has at least one rune!

		// set num of runes according to the room size
		for (int i = 0; i < iNumOfRunes; i++)
		{
			auto it = room.tiles.begin();
			std::advance(it, utils_rand(1, room.roomSize - 1));
			if (getMapValue(it->x, it->y) != cave_tile_rune) {

				// make sure the min distance btw two runes is 5 
				int surroundingEmptyTileNum = 0;
				for (int neighbourX = it->x - 2; neighbourX <= it->x + 2; neighbourX++)
					for (int neighbourY = it->y - 2; neighbourY <= it->y + 2; neighbourY++)
						if (isInBounds(neighbourX, neighbourY)) {
							if (getMapValue(neighbourX, neighbourY) != cave_tile_rune)
								++surroundingEmptyTileNum;
						}

				if (surroundingEmptyTileNum == 25) {
					setMapValue(it->x, it->y, cave_tile_rune); // set tile value
					 // create rune object
					RuneManager::getInstance()->initRuneAt(
						getTileWidth() * it->x + getTileWidth() / 2,
						getTileHeight() * it->y + getTileHeight() / 2
					);
				}
				else
					--i;
			}
			else
				--i;
		}
		for (auto const& it : room.tiles) {
			if (getMapValue(it.x, it.y) == cave_tile_rune)// set back to empty for spwaner checking
				setMapValue(it.x, it.y, cave_tile_empty);
		}
	}
}

void CaveGenerator::setOtherTileTypes() {
	for (int x = 0; x < m_iMapWidth; x++) {
		for (int y = 0; y < m_iMapHeight; y++) {

			if (getMapValue(x, y) == cave_tile_wall && isEdge(x, y)) {
				setMapValue(x, y, cave_tile_edge);
			}
			if (getMapValue(x, y) == cave_tile_empty && isSpawner(x, y)) {
				setMapValue(x, y, cave_tile_spawner);
			}
		}
	}
}

Vec2 CaveGenerator::initPlayerPosition() {
	while (1) {
		// keep player far from boundary enough
		int x = utils_rand(m_iMapWidth / 8, 7 * m_iMapWidth / 8);
		int y = utils_rand(m_iMapHeight / 8, 7 * m_iMapHeight / 8);

		// find an empty slot for player's initial position
		int surroundingEmptyTileNum = 0;
		for (int neighbourX = x - 2; neighbourX <= x + 2; neighbourX++)
			for (int neighbourY = y - 2; neighbourY <= y + 2; neighbourY++)
				if (isInBounds(neighbourX, neighbourY)) {
					if (getMapValue(neighbourX, neighbourY) == cave_tile_empty
						|| getMapValue(neighbourX, neighbourY) == cave_tile_spawner)
						++surroundingEmptyTileNum;
				}
		if (surroundingEmptyTileNum == 25) {
			return Vec2(
				x * m_iTileWidth + m_iTileWidth / 2,
				y * m_iTileHeight + m_iTileHeight / 2);
		}
	}
}

void CaveGenerator::connectClosestRooms(std::list<Room>& validRooms, bool forceAccessToMainRoom) {
	// because push_back function only push copy, so we use pointer here
	std::list<Room*> roomListIsolated; // rooms currently disconnected to main room
	std::list<Room*> roomListAccessible; // rooms currently connected to main room

	for (Room& room : validRooms) {
		if (forceAccessToMainRoom) { // see explain at the end of the function
			if (room.isAccessibleToMainRoom)
				roomListAccessible.push_back(&room);
			else
				roomListIsolated.push_back(&room);
		}
		else {
			roomListAccessible.push_back(&room);
			roomListIsolated.push_back(&room);
		}
	}

	int minDistance = 0; // minDistance btw two rooms, acc this is square of dist to reduce overhead
	Vec2 bestTileA; // best tiles to connect two rooms
	Vec2 bestTileB;
	Room* pBestRoomA;
	Room* pBestRoomB;
	bool PossibleConnectionFound = false;

	for (Room*& pRoomA : roomListIsolated) {
		if (!forceAccessToMainRoom) {
			PossibleConnectionFound = false;
			if (pRoomA->connectedRooms.size() > 0) // if already connected, skip
				continue;
		}

		for (Room*& pRoomB : roomListAccessible) {
			if (*pRoomA == *pRoomB || pRoomA->isConnected(*pRoomB))  // skip overlapped checking & skip checking on connected rooms
				continue;

			for (int tileIndexA = 0; tileIndexA < pRoomA->edgeTiles.size(); tileIndexA++) {
				for (int tileIndexB = 0; tileIndexB < pRoomB->edgeTiles.size(); tileIndexB++) {
					// find in list by index using iterator
					Vec2 tileA = *(std::next(pRoomA->edgeTiles.begin(), tileIndexA));
					Vec2 tileB = *(std::next(pRoomB->edgeTiles.begin(), tileIndexB));

					// dont need to sqrt to avoid overhead!!
					int distanceBtwRooms = (int)(pow(tileA.x - tileB.x, 2) + pow(tileA.y - tileB.y, 2));

					if (distanceBtwRooms < minDistance || !PossibleConnectionFound) {
						minDistance = distanceBtwRooms;
						PossibleConnectionFound = true;
						bestTileA = tileA;
						bestTileB = tileB;
						pBestRoomA = pRoomA;
						pBestRoomB = pRoomB;
					}
				}
			}
		}

		// creat connection passage btw rooms
		if (PossibleConnectionFound && !forceAccessToMainRoom) { // sublte! this is for finding the min distance when not forcing
			createPassage(pBestRoomA, pBestRoomB, bestTileA, bestTileB);
		}
	}
	// sublte! this is for finding the min distance when forcing
	// to avoid naive connec the first connection btw two rooms
	if (PossibleConnectionFound && forceAccessToMainRoom) {
		createPassage(pBestRoomA, pBestRoomB, bestTileA, bestTileB);
		// after this, keep check if there are more isolated rooms
		connectClosestRooms(validRooms, true);
	}

	// after firstly connecting rooms, check if there are any isolated rooms
	if (!forceAccessToMainRoom) {
		connectClosestRooms(validRooms, true);
	}
}

void CaveGenerator::createPassage(Room* pRoomA, Room* pRoomB, Vec2 tileA, Vec2 tileB) {
	Room::connectRooms(*pRoomA, *pRoomB);

	//test 
   /* pairList.push_back(PosPair(
		Pos(m_iBaseScreenX + getTileWidth() * tileA.x, m_iBaseScreenY + getTileHeight() * tileA.y),
		Pos(m_iBaseScreenX + getTileWidth() * tileB.x, m_iBaseScreenY + getTileHeight() * tileB.y)));*/

	std::list<Vec2> line = computeLine(tileA, tileB);
	for (Vec2 point : line) {
		drawCircle(point, passageSize, cave_tile_empty);
	}
}

// flood algorithm - flood and find all regions
void CaveGenerator::getRegions(int tileType, std::list<std::list<Vec2>>& regions) {

	int* pMapFlags = new int[m_iMapWidth * m_iMapHeight]{ 0 };
	// flood algorithm
	for (int x = 0; x < m_iMapWidth; x++) {
		for (int y = 0; y < m_iMapHeight; y++) {
			if (pMapFlags[utils_index(x, y, m_iMapWidth)] == 0 && getMapValue(x, y) == tileType) {
				std::list<Vec2> newRegion;
				getRegionTilesFrom(x, y, newRegion);
				regions.push_back(newRegion);

				for each (Vec2 Position in newRegion)
					pMapFlags[utils_index(Position.x, Position.y, m_iMapWidth)] = 1;
			}
		}
	}
	delete[] pMapFlags;
}

// flood algorithm - flood a single region
void CaveGenerator::getRegionTilesFrom(int startX, int startY, std::list<Vec2>& tiles) {

	int* pMapFlags = new int[m_iMapWidth * m_iMapHeight]{ 0 };
	int tileType = getMapValue(startX, startY);

	// use queue to enhance performance
	std::queue<Vec2> queue;
	queue.push(Vec2{ startX, startY }); // the start point of the algorithm
	pMapFlags[utils_index(startX, startY, m_iMapWidth)] = 1;

	while (queue.size() > 0) {
		Vec2 tile = queue.front();
		queue.pop();
		tiles.push_back(tile);

		for (int x = tile.x - 1; x <= tile.x + 1; x++) {
			for (int y = tile.y - 1; y <= tile.y + 1; y++) {
				if (isInBounds(x, y) && (x == tile.x || y == tile.y)) {
					if (pMapFlags[utils_index(x, y, m_iMapWidth)] == 0 && getMapValue(x, y) == tileType) {
						pMapFlags[utils_index(x, y, m_iMapWidth)] = 1;
						queue.push(Vec2{ x, y });
					}
				}
			}
		}
	}
	delete[] pMapFlags;
}

int CaveGenerator::getSurroundingWallCount(int x, int y) const {
	int wallCount = 0;
	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++)
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++)
			if (isInBounds(neighbourX, neighbourY)) {
				if (neighbourX != x || neighbourY != y)
					wallCount += getMapValue(neighbourX, neighbourY);
			} //!!!!!!!!!! cannot unbracket it - logic error !!!!!!!!!!!!!!!
			else
				wallCount++;
	return wallCount;
}

bool CaveGenerator::isEdge(int x, int y) const {
	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++)
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++)
			if (isInBounds(neighbourX, neighbourY)) {
				if (neighbourX != x || neighbourY != y) {
					if (getMapValue(neighbourX, neighbourY) == cave_tile_empty)
						return true;
				}
			}

	return false;
}

bool CaveGenerator::isSpawner(int x, int y) const {
	int surroundingEmptyTileNum = 0;
	for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX++)
		for (int neighbourY = y - 1; neighbourY <= y + 1; neighbourY++)
			if (isInBounds(neighbourX, neighbourY)) {
				if (neighbourX != x || neighbourY != y) {
					if (getMapValue(neighbourX, neighbourY) == cave_tile_empty)
						++surroundingEmptyTileNum;
				}
			}
	return surroundingEmptyTileNum == 8;
}