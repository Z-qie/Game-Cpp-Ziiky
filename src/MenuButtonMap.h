//#pragma once
//#include "Zy21586TileManager.h"
//
//constexpr auto menu_button_start = 0;
//constexpr auto menu_button_instruction = 1;
//constexpr auto menu_button_record = 2;
//constexpr auto menu_button_quit = 3;
//
//class MenuButtonMap : public Zy21586TileManager
//{
//protected:
//    // constructor
//    MenuButtonMap(
//        int iColNum = 1, // width/col of button list
//        int iRowNum = 4, // height/row of button list
//        int iButtonWidth = 180,  // size of button
//        int iButtonHeight = 50,
//        int iScreenX = 50,
//        int iScreenY = 450);
//
//    static MenuButtonMap* m_pMenuButtonMap;
//public:
//    static MenuButtonMap* getInstance();
//public:
//
//    virtual ~MenuButtonMap() override;
//
//    virtual void virtDrawTileAt(
//        BaseEngine* pEngine,
//        DrawingSurface* pSurface,
//        int iMapX,
//        int iMapY,
//        int iStartPositionScreenX,
//        int iStartPositionScreenY) const override;
//
//    void initMenuButtonMap();
//    void updateButtonMap();
//
//};
//
