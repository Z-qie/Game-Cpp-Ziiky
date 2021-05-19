

#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "ResultScene.h"
#include "GameObject.h"
#include "ResultUI.h"
#include "DiscardButtion.h"
#include "ConfirmButton.h"
#include "RecordManager.h"

void ResultScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
};

void ResultScene::onActivate()
{    // Resets the currentSeconds count whenever the scene is activated.

    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);
    pEngine->notifyObjectsAboutKeys(true);

    m_pDiscardButton = DiscardButtion::getInstance();
    m_pConfirmButton = ConfirmButton::getInstance();
    pResultUI = ResultUI::getInstance();

    int iCurrentGameObject = 0;
    int iGameObjectNum = 50;
    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, pResultUI);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pDiscardButton);
    pEngine->storeObjectInArray(++iCurrentGameObject, m_pConfirmButton);
    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuRecordButton);
    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuQuitButton);
    //std::cout << "onActivate done" << std::endl;

}

//int testInt = 2147483647;
void ResultScene::virtMainLoopPreUpdate() {
    //std::cout << "virtMainLoopPreUpdate" << std::endl;
    //std::cout << testInt / 1000 /60  << std::endl;
    pEngine->redrawDisplay();
    if (m_pDiscardButton->isClicked()) {
        SceneStateMachine::getInstance()->switchTo(SceneID::MENU);
    }

    // make sure the input is not empty
    if (m_pConfirmButton->isClicked() && pResultUI->getPlayerName() != "") {
        RecordManager::getInstance()->updateRecordToFile(pResultUI->getPlayerName());
        SceneStateMachine::getInstance()->switchTo(SceneID::MENU);
    }
}


void ResultScene::virtPreDraw() {
   


    //mouse position debug
    //char buf[128];
    //sprintf(buf, "Mouse X: %2d, Y: %2d", pEngine->getCurrentMouseX(), pEngine->getCurrentMouseY());
    //pEngine->drawForegroundString(20,100, buf, 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 15));
    //std::cout << pEngine->getForegroundSurface()->getDrawPointsFilter() << std::endl;
    //std::cout << pEngine->getBackgroundSurface()->getDrawPointsFilter() << std::endl;


}

void ResultScene::virtPostDraw() {
    //m_pMenuButtonMap->drawAllTiles(pEngine, pEngine->getForegroundSurface());
}


void ResultScene::onDeactivate() {
    pEngine->notifyObjectsAboutKeys(false);
}

void ResultScene::onDestroy() {

}
