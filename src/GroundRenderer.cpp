
#pragma once

#include "header.h"
#include "TileManager.h"
#include "Utils.h"
#include "GroundRenderer.h"
#include "CaveGenerator.h"
#include "Zy21586Engine.h"
#include "SimpleImage.h"
#include "ImagePixelMapping.h"
#include "Player.h"

GroundRenderer* GroundRenderer::pGroundRenderer = nullptr;

GroundRenderer::GroundRenderer(
    int caveWidth,
    int caveHeight,
    int tileSize)
    : Zy21586TileManager(caveWidth, caveHeight, tileSize)
{
    setTopLeftPositionOnScreen(0, 0);
    groundTileSprites[0] = ImageManager::get()->getImagebyURL("assets/sprites/CAVE_GROUND_01.png", true, true);
    groundTileSprites[1] = ImageManager::get()->getImagebyURL("assets/sprites/CAVE_GROUND_02.png", true, true);
    groundTileSprites[2] = ImageManager::get()->getImagebyURL("assets/sprites/CAVE_GROUND_03.png", true, true);
    groundTileSprites[3] = ImageManager::get()->getImagebyURL("assets/sprites/CAVE_GROUND_04.png", true, true);
    groundTileSprites[4] = ImageManager::get()->getImagebyURL("assets/sprites/CAVE_GROUND_05.png", true, true);
};

GroundRenderer* GroundRenderer::getInstance()
{
    if (pGroundRenderer == nullptr) {
        pGroundRenderer = new GroundRenderer();
    }
    return pGroundRenderer;
};

void GroundRenderer::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX,
    int iMapY,
    int iStartPositionScreenX,
    int iStartPositionScreenY) const {

    int tileValue = getMapValue(iMapX, iMapY);

    if (tileValue != ground_tile_00) {
        groundTileSprites[tileValue - 1].renderImage(
            pSurface,
            0, 0,
            iStartPositionScreenX,
            iStartPositionScreenY,
            groundTileSprites[tileValue - 1].getWidth(),
            groundTileSprites[tileValue - 1].getHeight()
        );
    }

    // randome texture 
    if (utils_rand(0, 1000) < 1)
        for (size_t i = 0; i < 4; i++)
        {
            pEngine->drawForegroundLine(
                iStartPositionScreenX + utils_rand(-30, 30),
                iStartPositionScreenY + utils_rand(-10, 10),
                iStartPositionScreenX + utils_rand(-30, 30),
                iStartPositionScreenY + utils_rand(-10, 10),
                0x000000);
        }
}

void GroundRenderer::randomFillSprite() {
    // select seed
    for (int x = 0; x < m_iMapWidth; x++)
        for (int y = 0; y < m_iMapHeight; y++) {
            int caveGeneratorTile = CaveGenerator::getInstance()->getMapValue(x, y);
            if (caveGeneratorTile == cave_tile_empty || caveGeneratorTile == cave_tile_spawner) {
                setMapValue(x, y,
                    (utils_rand(0, 100) < 5) ?
                    utils_rand(1, 5) // this represent ground_tile_01 to ground_tile_05
                    : ground_tile_00);
            }
            else
                setMapValue(x, y, ground_tile_00);
        }
}
