#pragma once

#include "header.h"
#include "LoadingScene.h"
#include "Zy21586Engine.h"
#include "ParticleMap.h"
#include "LoadingUI.h"

void LoadingScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
};

void LoadingScene::onActivate()
{    // Resets the currentSeconds count whenever the scene is activated.
    m_CurrentSTime = 0;
    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);

    m_pLoadingUI = LoadingUI::getInstance();
    m_pParticleMap = ParticleMap::getInstance();

    int iCurrentGameObject = 0;
    int iGameObjectNum = 50;
    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pLoadingUI);
}

void LoadingScene::setSwitchToScene(SceneID id)
{    // Stores the id of the scene that we will transition to.
    m_SceneSwitchedID = id;
}

void LoadingScene::virtMainLoopPreUpdate() {
    m_pParticleMap->updateParticleMap();

    pEngine->redrawDisplay();
    checkForTime();

}


//void LoadingScene::virtMouseDown(int iButton, int iX, int iY) {
//    //if (iButton == SDL_BUTTON_RIGHT) {
//    //    m_pParticleMap->setEmptyFollowMouse(true); // erase spirit particle
//    //}
//
//    //if (iButton == SDL_BUTTON_LEFT) {
//    //    m_pParticleMap->setSpiritFollowMouse(true); // generate spirit particle
//    //}
//
//}
//
//void LoadingScene::virtMouseUp(int iButton, int iX, int iY) {
//    //if (iButton == SDL_BUTTON_RIGHT) {
//    //    m_pParticleMap->setEmptyFollowMouse(false);//stop erasing spirit particle
//    //}
//
//    //if (iButton == SDL_BUTTON_LEFT) {
//    //    m_pParticleMap->setSpiritFollowMouse(false); // stop generating spirit particle
//    //}
//}


void LoadingScene::virtPreDraw() {
    Zy21586Engine::getInstance()->fillBackground(0x000000);

    m_pParticleMap->drawAllTiles(pEngine, pEngine->getBackgroundSurface());
}

void LoadingScene::checkForTime() {
    if (m_CurrentSTime == 0) {
        m_CurrentSTime = Zy21586Engine::getInstance()->getModifiedTime() + m_iDisplayInterval;
    }
    else if (m_CurrentSTime < Zy21586Engine::getInstance()->getModifiedTime())
    {// Switches states.
        SceneStateMachine::getInstance()->switchTo(m_SceneSwitchedID);
    }
}


void LoadingScene::virtKeyDown(int iKeyCode) {
    if (iKeyCode == SDLK_SPACE) {
        SceneStateMachine::getInstance()->switchTo(SceneID::GAME); //test
    }
    if (iKeyCode == SDLK_RETURN) {
        SceneStateMachine::getInstance()->switchTo(SceneID::MENU); //test
    }
}

void LoadingScene::onDeactivate() {
    delete m_pParticleMap;
    m_pParticleMap = nullptr;
}

void LoadingScene::onDestroy() {
    delete m_pParticleMap;
    std::cout << "LoadingScene destroy done" << std::endl;
}

