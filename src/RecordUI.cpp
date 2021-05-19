
#pragma once 

#include "header.h"
#include "RecordUI.h"
#include "RecordManager.h"


RecordUI* RecordUI::pRecordUI = nullptr;

RecordUI::RecordUI() {

    //BG image
    sprite = ImageManager::get()->getImagebyURL("assets/sprites/WIN_BG_02.png", true, true);
};

RecordUI* RecordUI::getInstance()
{
    if (pRecordUI == nullptr) {
        pRecordUI = new RecordUI();
    }
    return pRecordUI;
}

void RecordUI::virtDraw() {
    if (!isVisible()) return;
    drawReturnButton();
    drawBackground();
    drawBoardFrame();
    drawRecord();
}


void RecordUI::drawReturnButton() {
    m_pEngine->drawForegroundString(
        10 + utils_rand(-1, 1), // x
        6 + utils_rand(-1, 1), // y
        "MENU : ESC",
        0xe7fbff, 
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 30)
    );
}
void RecordUI::drawRecord() {
    std::vector<std::string> result = RecordManager::getInstance()->decodeRecord();
    // Title
    m_pEngine->drawForegroundString(
        170 - 1, // x
        130, // y
        "R E C O R D",
        0xfc59cc,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
    m_pEngine->drawForegroundString(
        170 + 1, // x
        130, // y
        "R E C O R D",
        0x2ed082,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
    m_pEngine->drawForegroundString(
        170, // x
        130, // y
        "R E C O R D",
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
   
    // TIME: 
    //            (LONGEST: xx:xx by XXXX)
    //            (SHORTEST: xx:xx by XXXX)
    m_pEngine->drawForegroundString(
        170,
        250,
        result[0].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    m_pEngine->drawForegroundString(
        190,
        280,
        result[1].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    m_pEngine->drawForegroundString(
        190,
        310,
        result[2].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    // KILL: xx    [RECORD!] (Best: 100 by XXXX)
    m_pEngine->drawForegroundString(
        170,
        360,
        result[3].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    // HP: xx [RECORD!] (Best: 100 by XXXX)
    m_pEngine->drawForegroundString(
        170,
        410,
        result[4].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
}

void RecordUI::drawBackground() {
    m_pSpriteMapping->setBrightnessPercentage(40);
    //The xand y locationand the widthand height on the surface to draw to
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getBackgroundSurface(),
        0,
        0,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);
}

void RecordUI::drawBoardFrame() {
    // gonna hard code this....lazy me jaja
    m_pEngine->drawForegroundLine(
        100 + utils_rand(-1, 1) - 10,
        100 + utils_rand(-1, 1),
        620 + utils_rand(-1, 1) + 10,
        100 + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        100 + utils_rand(-1, 1),
        100 + utils_rand(-1, 1) - 10,
        100 + utils_rand(-1, 1),
        460 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        100 + utils_rand(-1, 1) - 10,
        460 + utils_rand(-1, 1),
        620 + utils_rand(-1, 1) + 10,
        460 + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        620 + utils_rand(-1, 1),
        100 + utils_rand(-1, 1) - 10,
        620 + utils_rand(-1, 1),
        460 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );
}


void RecordUI::virtDoUpdate(int iCurrentTime) {

}

