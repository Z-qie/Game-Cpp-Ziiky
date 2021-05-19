#pragma once 

#include "header.h"
#include "PauseUI.h"
#include "GameCamera.h"


PauseUI* PauseUI::pPauseUI = nullptr;

PauseUI::PauseUI() {
    sprite = ImageManager::get()->getImagebyURL("assets/sprites/PAUSE_BG.png", true, true);
};

PauseUI* PauseUI::getInstance()
{
    if (pPauseUI == nullptr) {
        pPauseUI = new PauseUI();
    }
    return pPauseUI;
}

void PauseUI::drawUI() {
    // bing with camera position
    GameCamera* pCamera = GameCamera::getInstance();
    setPosition(pCamera->getCameraPosition() + Vec2{ -base_window_width / 2 ,-base_window_height / 2 });
    
    
    // if paused then draw paused UI
    if (m_pEngine->isPaused()) {
        m_pSpriteMapping->setMergePercentage(75);
        m_pSpriteMapping->setTopLeftPositionInImage(m_iOffsetXBG++, 0);
        //The xand y locationand the widthand height on the surface to draw to
        sprite.renderImageApplyingMapping(
            m_pEngine,
            m_pEngine->getForegroundSurface(),
            getPosition().x,
            getPosition().y,
            sprite.getWidth(),
            sprite.getHeight(),
            m_pSpriteMapping);

        // resume and quit
        m_pEngine->drawForegroundString(
            getPosition().x + 260 + utils_rand(-1, 1),
            getPosition().y + 660,
            "Press SPACE to resume, ESC to menu", /*0xd9f5ff*/0xe7fbff,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 25));
       

        m_pEngine->drawForegroundString(
            getPosition().x + m_iOffsetTitle.x + utils_rand(-1, 0),
            getPosition().y + m_iOffsetTitle.y,
            "- PAUSE -", 0xfc59cc,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 80));
        m_pEngine->drawForegroundString(
            getPosition().x + m_iOffsetTitle.x + utils_rand(1, 0),
            getPosition().y + m_iOffsetTitle.y,
            "- PAUSE -", 0x2ed082,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 80));
        m_pEngine->drawForegroundString(
            getPosition().x + m_iOffsetTitle.x,
            getPosition().y + m_iOffsetTitle.y,
            "- PAUSE -", 0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 80));
    }
    // if not paused then draw pause instruction
    else {
        // resume
        m_pEngine->drawForegroundString(
            getPosition().x + 300,
            getPosition().y + 660,
            "Press SPACE to pause", /*0xd9f5ff*/0xe7fbff,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 25));
    }

   

}

void PauseUI::virtDoUpdate(int iCurrentTime) {

}

