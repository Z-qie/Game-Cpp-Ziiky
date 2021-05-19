
#pragma once 

#include "header.h"
#include "WinUI.h"
#include "GameCamera.h"
#include "Animator.h"
#include "Animation.h"

#include "Zy21586Engine.h"

WinUI* WinUI::pWinUI = nullptr;

WinUI::WinUI()
    :m_pAnimator(new Animator<WinUIState>()) {
    virtStart();
};

WinUI* WinUI::getInstance()
{
    if (pWinUI == nullptr) {
        pWinUI = new WinUI();
    }
    return pWinUI;
}


void WinUI::virtStart() {
    std::shared_ptr<Animation> pWinLightening = std::make_shared<Animation>(0);

    pWinLightening->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WIN_BG_01.png", true, true));
    pWinLightening->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WIN_BG_02.png", true, true));

    m_pAnimator->addAnimation(WinUIState::WIN_LIGHTENGING, pWinLightening);
    m_pAnimator->setAnimationState(winUIState);

}

void WinUI::drawUI() {
    // bing with camera position
    GameCamera* pCamera = GameCamera::getInstance();
    setPosition(pCamera->getCameraPosition() + Vec2{ -base_window_width / 2 ,-base_window_height / 2 });

    sprite = m_pAnimator->play();
    // display gameover bg wit easeIn
    m_pSpriteMapping->setMergePercentage(static_cast<int>(m_fMergePercentage = utils_lerp(m_fMergePercentage, 100.f, 0.03f)));
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
        getPosition().x + 270 + utils_rand(-1, 0),
        getPosition().y + 140,
        "C O N G R A T S",
        0x2ed082,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 55));
    m_pEngine->drawForegroundString(
        getPosition().x + 270 + utils_rand(1, 0),
        getPosition().y + 140,
        "C O N G R A T S",
        0xfc59cc,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 55));
    m_pEngine->drawForegroundString(
        getPosition().x + 270,
        getPosition().y + 140,
        "C O N G R A T S",
        0xe7fbff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 55));
    m_pEngine->drawForegroundString(
        getPosition().x + 280 + utils_rand(-1, 1),
        getPosition().y + 200,
        "Press  SPACE  to continue", /*0xd9f5ff*/0xe7fbff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 25));


    m_pEngine->drawForegroundString(
        getPosition().x + m_iOffsetTitle.x + utils_rand(-1, 1),
        getPosition().y + m_iOffsetTitle.y,
        "Z i i k y", 0xd9f5ff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 80));

    //drawLighteningEffect();
}
/*
void drawLighteningEffect() {
    Vec2 m_oStart{ 0,0 };
    Vec2 m_oTarget{ 0,0 };
    int m_iNextFlashTime{ 0 };
    int m_iFlashEndTime{ 0 };
    int m_iNumOfBreakPoint{ 0 };
    std::queue<Vec2> m_oThunderFlashLine01;
    std::list<std::queue<Vec2>> m_oThunderList;

    m_oThunderFlashLine.swap(std::queue<Vec2>()); // clear last flash form
    m_oThunderFlashLine.push(m_oStart);

    for (int i = 0; i < m_iNumOfBreakPoint - 1; i++)
    {
        m_oThunderFlashLine.push(Vec2{
            m_oStart.x + utils_rand(-iRandomOffsetThresholdX, iRandomOffsetThresholdX),
            m_oStart.y + i * iBoltBreakPointDist + utils_rand(-iRandomOffsetThresholdY, iRandomOffsetThresholdY) });
    }

    m_oThunderFlashLine.push(m_oTarget);
}

void drawAllThunderBolts(std::queue<Vec2>& rLine) {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    // flash line
    Vec2 start = rLine.front();
    rLine.pop();

    while (!rLine.empty())
    {
        Vec2 next = rLine.front();
        pEngine->drawBackgroundThickLine(
            start.x, start.y,
            next.x, next.y,
            0xd3f3ff
            , 3);

        pEngine->drawForegroundLine(
            start.x, start.y,
            next.x, next.y,
            0xffffff);

        start = next;
        rLine.pop();
    }
}
*/
void WinUI::virtDoUpdate(int iCurrentTime) {

}

