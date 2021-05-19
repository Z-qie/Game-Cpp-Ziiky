//#pragma once
//
//#include "header.h"
//#include "Zy21586Engine.h"
//#include "Utils.h"
//#include "MenuButtonMap.h"
//
//MenuButtonMap* MenuButtonMap::m_pMenuButtonMap = nullptr;
//
//MenuButtonMap* MenuButtonMap::getInstance()
//{
//    if (m_pMenuButtonMap == nullptr) {
//        m_pMenuButtonMap = new MenuButtonMap();
//    }
//    return m_pMenuButtonMap;
//};
//
//// constructor
//MenuButtonMap::MenuButtonMap(
//        int iColNum, // width/col of button list
//        int iRowNum, // height/row of button list
//        int iButtonWidth,  // size of button
//        int iButtonHeight,
//        int iScreenX,
//        int iScreenY)
//    :Zy21586TileManager(iColNum, iRowNum, iButtonHeight, iButtonWidth)
//{
//    setTopLeftPositionOnScreen(iScreenX, iScreenY);
//    //initParticleMap();
//}
//
//MenuButtonMap::~MenuButtonMap()
//{
//   :m_pMenuButtonMap = nullptr;
//}
//
//void MenuButtonMap::initMenuButtonMap() {
//    setMapValue(0, 0, menu_button_start);
//    setMapValue(0, 1, menu_button_instruction);
//    setMapValue(0, 2, menu_button_record);
//    setMapValue(0, 3, menu_button_quit);
//}
//
//void MenuButtonMap::updateButtonMap() {
//
//}
//
//void MenuButtonMap::virtDrawTileAt(
//    BaseEngine* pEngine,
//    DrawingSurface* pSurface,
//    int iMapX,
//    int iMapY,
//    int iStartPositionScreenX,
//    int iStartPositionScreenY) const {
//
//    pSurface->drawRectangle(
//        iStartPositionScreenX,	// Left
//        iStartPositionScreenY + 10,	// Top
//        iStartPositionScreenX + getTileWidth() - 1 ,		// Right
//        iStartPositionScreenY + getTileHeight() - 1 - 10,	// Bottom
//        0x565656);	// Pixel colour
//
//
//}