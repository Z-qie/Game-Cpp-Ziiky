


#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "RecordScene.h"
#include "GameObject.h"
#include "RecordUI.h"
#include "ResetButton.h"
#include "RecordManager.h"

void RecordScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
};

void RecordScene::onActivate()
{    // Resets the currentSeconds count whenever the scene is activated.

    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);
    pEngine->notifyObjectsAboutKeys(true);

    pResetButton = ResetButton::getInstance();
    pRecordUI = RecordUI::getInstance();

    int iCurrentGameObject = 0;
    int iGameObjectNum = 5;
    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, pRecordUI);
    pEngine->storeObjectInArray(++iCurrentGameObject, pResetButton);
    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuRecordButton);
    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuQuitButton);
    //std::cout << "onActivate done" << std::endl;

}

void RecordScene::virtMainLoopPreUpdate() {
    //std::cout << "virtMainLoopPreUpdate" << std::endl;
    //std::cout << testInt / 1000 /60  << std::endl;
    if (pResetButton->isClicked()) {
        RecordManager::getInstance()->resetRecordFile();
    }
    pEngine->redrawDisplay();

}


void RecordScene::virtPreDraw() {
}

void RecordScene::virtPostDraw() {
    //m_pMenuButtonMap->drawAllTiles(pEngine, pEngine->getForegroundSurface());
}

void RecordScene::virtKeyDown(int iKeyCode) {
    if (iKeyCode == SDLK_ESCAPE) {
        SceneStateMachine::getInstance()->switchTo(SceneID::MENU);
    }
}


void RecordScene::onDeactivate() {
}

void RecordScene::onDestroy() {

}
