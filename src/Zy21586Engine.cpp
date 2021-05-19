#pragma once
#include <vector>

#include "header.h"
#include "Zy21586Engine.h"
#include "SceneStateMachine.h"
#include "RecordManager.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "IntroScene.h"
#include "RecordScene.h"


Zy21586Engine* Zy21586Engine::pMyEngine = nullptr;

Zy21586Engine* Zy21586Engine::getInstance()
{
    if (pMyEngine == nullptr) {
        pMyEngine = new Zy21586Engine();
    }
    return pMyEngine;
}

Zy21586Engine::Zy21586Engine()
    : pSceneStateMachine(SceneStateMachine::getInstance())
    , pRecordManager(RecordManager::getInstance())
{
    m_iDefaultUpdatePeriod = fixed_update_in_millis; // Change default update rate to 500ms
};

//void Zy21586Engine::virtSetupBackgroundBuffer()
//{
//} 

int Zy21586Engine::virtInitialiseObjects() {
    std::shared_ptr<MenuScene> pMenuScene = std::make_shared<MenuScene>();
    std::shared_ptr<LoadingScene> pLoadingScene = std::make_shared<LoadingScene>();
    std::shared_ptr<GameScene> pGameScene = std::make_shared<GameScene>();
    std::shared_ptr<ResultScene> pResultScene = std::make_shared<ResultScene>();
    std::shared_ptr<IntroScene> pIntroScene = std::make_shared<IntroScene>();
    std::shared_ptr<RecordScene> pRecordScene = std::make_shared<RecordScene>();



    pSceneStateMachine->addScene(pMenuScene, SceneID::MENU);
    pSceneStateMachine->addScene(pLoadingScene, SceneID::LOADING);
    pSceneStateMachine->addScene(pGameScene, SceneID::GAME);
    pSceneStateMachine->addScene(pResultScene, SceneID::RESULT);
    pSceneStateMachine->addScene(pIntroScene, SceneID::INSTRUCTION);
    pSceneStateMachine->addScene(pRecordScene, SceneID::RECORD);

    pLoadingScene->setSwitchToScene(SceneID::GAME);

    pSceneStateMachine->switchTo(SceneID::MENU);
    //pSceneStateMachine->switchTo(SceneID::INSTRUCTION);
    //pSceneStateMachine->switchTo(SceneID::RECORD);
    //pSceneStateMachine->switchTo(SceneID::GAME);
    //pSceneStateMachine->switchTo(SceneID::RESULT);
    return 0;
}

void Zy21586Engine::virtMainLoopPreUpdate() {
    pSceneStateMachine->virtMainLoopPreUpdate();
}

void Zy21586Engine::virtMainLoopPostUpdate() {
    pSceneStateMachine->virtMainLoopPostUpdate();
}

void Zy21586Engine::virtMainLoopDoBeforeUpdate() {
    pSceneStateMachine->virtMainLoopDoBeforeUpdate();
}

void Zy21586Engine::virtMainLoopDoAfterUpdate() {
    pSceneStateMachine->virtMainLoopDoAfterUpdate();
}

void Zy21586Engine::virtPreDraw() {
    pSceneStateMachine->virtPreDraw();
}

void Zy21586Engine::virtPostDraw() {
    pSceneStateMachine->virtPostDraw();
}

void Zy21586Engine::virtDrawStringsUnderneath() {
    pSceneStateMachine->virtDrawStringsUnderneath();
}

void Zy21586Engine::virtDrawStringsOnTop(){
    pSceneStateMachine->virtDrawStringsOnTop();
}

void Zy21586Engine::virtMouseDown(int iButton, int iX, int iY) {
    pSceneStateMachine->virtMouseDown(iButton, iX, iY);
}

void Zy21586Engine::virtMouseUp(int iButton, int iX, int iY) {
    pSceneStateMachine->virtMouseUp(iButton, iX, iY);
}

void Zy21586Engine::virtKeyDown(int iKeyCode)
{
    pSceneStateMachine->virtKeyDown(iKeyCode);
    switch (iKeyCode)
    {
    case SDLK_SPACE:
        //m_oCaveGenerator.generateCave();
        //m_oCaveGenerator.drawAllTiles(this, getBackgroundSurface());
     /*   if (isPaused())
            unpause();
        else
            pause();*/
        break;
    case SDLK_o:
        //m_oCaveGenerator.refineMap(); // test
        break;
    case SDLK_p:
        //m_oCaveGenerator.smoothMap(); // test
        break;

    //case SDLK_ESCAPE: // End program when escape is pressed
    //    setExitWithCode(0);
    //    break;
    }
}


void Zy21586Engine::virtCleanUp() {
    pSceneStateMachine->remove(SceneID::MENU);
    pSceneStateMachine->remove(SceneID::LOADING);
    pSceneStateMachine->remove(SceneID::GAME);

    delete pSceneStateMachine;
    delete pRecordManager;
}














