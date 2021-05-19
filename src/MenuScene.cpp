
#pragma once

#include "header.h"
#include "MenuScene.h"
#include "Zy21586Engine.h"
#include "ParticleMap.h"
#include "SceneBG.h"
#include "MenuStartButton.h"
#include "MenuIntroButton.h"
#include "MenuRecordButton.h"
#include "MenuQuitButton.h"
#include "CaveGenerator.h"


void MenuScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
};

void MenuScene::onActivate()
{    // Resets the currentSeconds count whenever the scene is activated.

    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);

    m_pParticleMap = ParticleMap::getInstance();

    m_pSceneBG = new SceneBG(); // animated background image
    m_pMenuStartButton = MenuStartButton::getInstance();
    m_pMenuIntroButton = MenuIntroButton::getInstance();
    m_pMenuRecordButton = MenuRecordButton::getInstance();
    m_pMenuQuitButton = MenuQuitButton::getInstance();
    int iCurrentGameObject = 0;
    int iGameObjectNum = 50;

    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pSceneBG);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuStartButton);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuIntroButton);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuRecordButton);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuQuitButton);
    //std::cout << "onActivate done" << std::endl;

}

//int testInt = 2147483647;
void MenuScene::virtMainLoopPreUpdate() {
    //std::cout << "virtMainLoopPreUpdate" << std::endl;
    //std::cout << testInt / 1000 /60  << std::endl;
    m_pParticleMap->updateParticleMap();
    pEngine->redrawDisplay();

    if (m_pMenuStartButton->isClicked()) {
        //SceneStateMachine::getInstance()->switchTo(SceneID::GAME);
        CaveGenerator::setSeed();// set random seed of CaveGenerator
        SceneStateMachine::getInstance()->switchTo(SceneID::LOADING);
    }
    if (m_pMenuQuitButton->isClicked()) {
        pEngine->setExitWithCode(0);
    }
    if (m_pMenuIntroButton->isClicked()) {
        SceneStateMachine::getInstance()->switchTo(SceneID::INSTRUCTION);
    }
    if (m_pMenuRecordButton->isClicked()) {
        SceneStateMachine::getInstance()->switchTo(SceneID::RECORD);
    }

}

void MenuScene::virtMouseDown(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_RIGHT) {
        m_pParticleMap->setEmptyFollowMouse(true); // erase spirit particle
    }

    if (iButton == SDL_BUTTON_LEFT) {

        m_pParticleMap->setSpiritFollowMouse(true); // generate spirit particle
    }

}

void MenuScene::virtMouseUp(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_RIGHT) {
        m_pParticleMap->setEmptyFollowMouse(false);//stop erasing spirit particle
    }

    if (iButton == SDL_BUTTON_LEFT) {
        m_pParticleMap->setSpiritFollowMouse(false); // stop generating spirit particle
    }
}

void MenuScene::virtPreDraw() {
    m_pParticleMap->drawAllTiles(pEngine, pEngine->getForegroundSurface());
}

void MenuScene::virtPostDraw() {
    //m_pMenuButtonMap->drawAllTiles(pEngine, pEngine->getForegroundSurface());
}

void MenuScene::onDeactivate() {
    delete m_pParticleMap;
    m_pParticleMap = nullptr;
}

void MenuScene::onDestroy() {
    delete m_pParticleMap;
    std::cout << "MenuScene destroy done" << std::endl;
}