#pragma once

#include <string>
#include <list>

#include "header.h"
#include "TileManager.h"
#include "Zy21586TileManager.h"
#include "Utils.h"

using namespace std;

struct Vec2;
struct PosPair;

bool Zy21586TileManager::isInBounds(int x, int y) const {
    if (x >= 0 && x < m_iMapWidth && y >= 0 && y < m_iMapHeight)
        return true;
    return false;
}

bool Zy21586TileManager::isEmpty(int x, int y) const {
    return (isInBounds(x, y) && getMapValue(x, y) == 0);
}

void Zy21586TileManager::drawCircle(Vec2 point, int radius, int value) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                int drawX = point.x + x;
                int drawY = point.y + y;
                if (isInBounds(drawX, drawY)) {
                    setMapValue(drawX, drawY, value); //TBC
                }
            }
        }
    }
}

// this returns the list of vec2 that intersected with the line given
list<Vec2> Zy21586TileManager::computeLine(Vec2 from, Vec2 to) {
    list<Vec2> line;

    int x = from.x;
    int y = from.y;

    int deltaX = to.x - from.x;
    int deltaY = to.y - from.y;

    bool inverted = false;
    int step = utils_get_sign(deltaX);
    int gradientStep = utils_get_sign(deltaY);

    int longest = abs(deltaX);
    int shortest = abs(deltaY);
 
    if (longest < shortest) {
        inverted = true;
        longest = abs(deltaY);
        shortest = abs(deltaX);

        step = utils_get_sign(deltaY);
        gradientStep = utils_get_sign(deltaX);
    }

    int gradientAccumulation = longest / 2;
    for (int i = 0; i < longest; i++) {
        line.push_back(Vec2(x, y));

        if (inverted) 
            y += step;
        else 
            x += step;
       
        gradientAccumulation += shortest;
        if (gradientAccumulation >= longest) {
            if (inverted) {
                x += gradientStep;
            }
            else {
                y += gradientStep;
            }
            gradientAccumulation -= longest;
        }
    }

    return line;
}