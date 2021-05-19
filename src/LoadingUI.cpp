
#pragma once 

#include "header.h"
#include "LoadingUI.h"
#include "CaveGenerator.h"
#include <string>

LoadingUI* LoadingUI::pLoadingUI = nullptr;

LoadingUI::LoadingUI()
    : m_pAnimator(new Animator<LoadingUIState>())
{
    virtStart();
};

LoadingUI* LoadingUI::getInstance()
{
    if (pLoadingUI == nullptr) {
        pLoadingUI = new LoadingUI();
    }
    return pLoadingUI;
}


void LoadingUI::virtStart() {
    std::shared_ptr<Animation> pLoadIdle = std::make_shared<Animation>(200);
    pLoadIdle->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/LOAD_BG_01.png", true, true));
    pLoadIdle->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/LOAD_BG_02.png", true, true));
    pLoadIdle->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/LOAD_BG_03.png", true, true));
    pLoadIdle->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/LOAD_BG_04.png", true, true));

    m_pAnimator->addAnimation(LoadingUIState::LOAD_IDLE, pLoadIdle);
    m_pAnimator->setAnimationState(LoadingUIState::LOAD_IDLE);

    m_iStartTime = m_pEngine->getModifiedTime();
}

void LoadingUI::virtDraw() {
    if (!isVisible()) return;

    // draw BG
    sprite = m_pAnimator->play();
    m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getForegroundSurface(),
        getPosition().x,
        getPosition().y,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);


    // info

//seed: xxxxxxx
    m_iCurrentTime = m_pEngine->getModifiedTime();
    if (m_iCurrentTime - m_iStartTime > 500) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 490,
            (std::string("seed: ") + std::to_string(CaveGenerator::getSeed())).c_str(),
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //generating cave map
    if (m_iCurrentTime - m_iStartTime > 1000) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 510,
            "generating  cave  map...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //generating cave environments
    if (m_iCurrentTime - m_iStartTime > 1500) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 530,
            "generating cave environments...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //generating runes
    if (m_iCurrentTime - m_iStartTime > 2000) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 550,
            "generating runes...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //initializing emenies
    if (m_iCurrentTime - m_iStartTime > 2500) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 570,
            "initialising emenies...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //initializing player
    if (m_iCurrentTime - m_iStartTime > 3000) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 590,
            "initialising player...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //initializing spell system
    if (m_iCurrentTime - m_iStartTime > 3500) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 610,
            "initialising spell system...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //initializing camera
    if (m_iCurrentTime - m_iStartTime > 4000) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 630,
            "initialising camera...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
    //initializing UIs
    if (m_iCurrentTime - m_iStartTime > 4500) {
        m_pEngine->drawForegroundString(
            getPosition().x + 10 + utils_rand(-1, 0),
            getPosition().y + 650,
            "initialising UIs...",
            0xffffff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf", 20));
    }
}



void LoadingUI::virtDoUpdate(int iCurrentTime) {

}
