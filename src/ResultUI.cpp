
#pragma once 

#include "header.h"
#include "ResultUI.h"
#include "RecordManager.h"


ResultUI* ResultUI::pResultUI = nullptr;

ResultUI::ResultUI() {
    /* m_iTotalRuneNum = RuneManager::getInstance()->getTotalRuneNum();
     m_iTimeOffset = Zy21586Engine::getInstance()->getModifiedTime();*/
     //BG image
    sprite = ImageManager::get()->getImagebyURL("assets/sprites/WIN_BG_01.png", true, true);
};

ResultUI* ResultUI::getInstance()
{
    if (pResultUI == nullptr) {
        pResultUI = new ResultUI();
    }
    return pResultUI;
}

void ResultUI::virtDraw() {
    if (!isVisible()) return;
    drawBackground();
    drawBoardFrame();
    drawResult();
}

void ResultUI::drawResult() {
    std::vector<std::string> result = RecordManager::getInstance()->decodeResult();
    // Title
    m_pEngine->drawForegroundString(
        170 - 1, // x
        130, // y
        "R E S U L T",
        0xfc59cc,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
    m_pEngine->drawForegroundString(
        170 + 1, // x
        130, // y
        "R E S U L T",
        0x2ed082,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
    m_pEngine->drawForegroundString(
        170, // x
        130, // y
        "R E S U L T",
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 50)
    );
    // RUNE ACTIVITED: xx
    m_pEngine->drawForegroundString(
        170,
        220,
        result[0].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    // TIME: xx:xx 
    //             [RECORD!] (LONGEST: xx:xx by XXXX)
    //             [RECORD!] (SHORTEST: xx:xx by XXXX)
    m_pEngine->drawForegroundString(
        170,
        250,
        result[1].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    m_pEngine->drawForegroundString(
        170,
        280,
        result[2].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    m_pEngine->drawForegroundString(
        170,
        310,
        result[3].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    // KILL: xx    [RECORD!] (Best: 100 by XXXX)
    m_pEngine->drawForegroundString(
        170,
        340,
        result[4].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
    // HP: xx [RECORD!] (Best: 100 by XXXX)
    m_pEngine->drawForegroundString(
        170,
        370,
        result[5].c_str(),
        0xffffff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
    );
}

void ResultUI::drawBackground() {
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

void ResultUI::drawBoardFrame() {
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
        420 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        100 + utils_rand(-1, 1) - 10,
        420 + utils_rand(-1, 1),
        620 + utils_rand(-1, 1) + 10,
        420 + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        620 + utils_rand(-1, 1),
        100 + utils_rand(-1, 1) - 10,
        620 + utils_rand(-1, 1),
        420 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );

    // input bar
    m_pEngine->drawForegroundLine(
        260 + utils_rand(-1, 1) - 10,
        500 + utils_rand(-1, 1),
        460 + utils_rand(-1, 1) + 10,
        500 + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        260 + utils_rand(-1, 1),
        500 + utils_rand(-1, 1) - 10,
        260 + utils_rand(-1, 1),
        540 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        260 + utils_rand(-1, 1) - 10,
        540 + utils_rand(-1, 1),
        460 + utils_rand(-1, 1) + 10,
        540 + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        460 + utils_rand(-1, 1),
        500 + utils_rand(-1, 1) - 10,
        460 + utils_rand(-1, 1),
        540 + utils_rand(-1, 1) + 10,
        0xe7fbff
    );

    // title
    m_pEngine->drawForegroundString(
        190 - 1, // x
        455, // y
        "INPUT NAME: (25 ALPHABETIC CHARACTERS MAX)",
        0x2ed082,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 18)
    ); m_pEngine->drawForegroundString(
        190 + 1, // x
        455, // y
        "INPUT NAME: (25 ALPHABETIC CHARACTERS MAX)",
        0xfc59cc,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 18)
    );
    m_pEngine->drawForegroundString(
        190, // x
        455, // y
        "INPUT NAME: (25 ALPHABETIC CHARACTERS MAX)",
        0xe7fbff,
        m_pEngine->getFont("assets/fonts/PixelFont.ttf", 18)
    );
   
    // name input
    m_pEngine->drawForegroundString(
        275, // x
        505, // y
        (">>  " + userInput + "  <<").c_str(),
        0xe7fbff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 23)
    );

}


void ResultUI::virtDoUpdate(int iCurrentTime) {

}

void ResultUI::virtKeyDown(int iKeyCode) {
    // input
    if ((iKeyCode >= SDLK_a && iKeyCode <= SDLK_z) || // a-z
        (iKeyCode >= SDLK_0 && iKeyCode <= SDLK_9)) // 0-9
    {
        if (userInput.size() <= 25)
            userInput += toupper(iKeyCode);
    }

    // delete
    if (iKeyCode == SDLK_BACKSPACE && userInput.size() != 0) {
        userInput.pop_back();
    }
}


std::string ResultUI::getPlayerName() {
    return userInput;
}
