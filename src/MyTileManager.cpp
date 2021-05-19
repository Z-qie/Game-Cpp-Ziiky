#include "header.h"
#include "MyTileManager.h"

MyTileManager::MyTileManager()
    : TileManager(20, 20, 20, 20)
{}

void MyTileManager::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX, int iMapY,
    int iStartPositionScreenX, int iStartPositionScreenY) const
{
#if 0
    int iMapValue = getMapValue(iMapX, iMapY);
    unsigned int iColour = 0x101010 * ((iMapX + iMapY + iMapValue) % 16);
    pSurface->drawRectangle(
        iStartPositionScreenX, // Left
        iStartPositionScreenY, // Top
        iStartPositionScreenX + getTileWidth() - 1, // Right
        iStartPositionScreenY + getTileHeight() - 1, // Bottom
        iColour); // Pixel colour
#endif

#if 1
    int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
    unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
        + (unsigned int)((iMapValue & 0xf0) << 8) // green
        + (unsigned int)((iMapValue & 0xf) << 4); // blue
    pSurface->drawOval(
        iStartPositionScreenX, // Left
        iStartPositionScreenY, // Top
        iStartPositionScreenX + getTileWidth() - 1, // Right
        iStartPositionScreenY + getTileHeight() - 1, // Bottom
        iColour);
#endif
};

