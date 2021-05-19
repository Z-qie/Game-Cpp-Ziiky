
#pragma once 

#include "header.h"
#include "GameOverUI.h"
#include "GameCamera.h"


GameOverUI* GameOverUI::pGameOverUI = nullptr;

GameOverUI::GameOverUI() {
    sprite = ImageManager::get()->getImagebyURL("assets/sprites/GAME_OVER_BG.png", true, true);
};

GameOverUI* GameOverUI::getInstance()
{
    if (pGameOverUI == nullptr) {
        pGameOverUI = new GameOverUI();
    }
    return pGameOverUI;
}

void GameOverUI::drawUI() {
    // bing with camera position
        GameCamera* pCamera = GameCamera::getInstance();
        setPosition(pCamera->getCameraPosition() + Vec2{ -base_window_width / 2 ,-base_window_height / 2 });

        // display gameover bg wit easeIn
        m_pSpriteMapping->setMergePercentage(static_cast<int>(m_fMergePercentage = utils_lerp(m_fMergePercentage, 85.f, 0.03f)));
        m_pSpriteMapping->setTopLeftPositionInImage(0, 0);
        //The xand y locationand the widthand height on the surface to draw to
        sprite.renderImageApplyingMapping(
            m_pEngine,
            m_pEngine->getForegroundSurface(),
            getPosition().x,
            getPosition().y,
            sprite.getWidth(),
            sprite.getHeight(),
            m_pSpriteMapping);

        // restart and quit
        m_pEngine->drawForegroundString(
            getPosition().x + 260 + utils_rand(-1, 1),
            getPosition().y + 660,
            "Press  SPACE  to  play  again,  ESC  to  menu", /*0xd9f5ff*/0xe7fbff,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 25));

        // title 
        m_pEngine->drawForegroundString(
            getPosition().x + m_iOffsetTitle.x + utils_rand(-2, 2),
            getPosition().y + m_iOffsetTitle.y,
            "- The  End  Of  A  NightMare -", 0x8e0000,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 45));
       
        m_pEngine->drawForegroundString(
            getPosition().x + m_iOffsetTitle.x,
            getPosition().y + m_iOffsetTitle.y,
            "- The  End  Of  A  NightMare -", 0x581414,
            m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 45));

}

void GameOverUI::virtDoUpdate(int iCurrentTime) {

}

