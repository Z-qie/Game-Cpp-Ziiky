


#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "GameObject.h"
#include "IntroScene.h"
#include "ViewCamera.h"
#include "InstructionUI.h"

void IntroScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
};

void IntroScene::onActivate()
{    // Resets the currentSeconds count whenever the scene is activated.

    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);
    pEngine->notifyObjectsAboutKeys(true);

    int iCurrentGameObject = 0;
    int iGameObjectNum = 3;

    pViewCamera = ViewCamera::getInstance();
    pViewCamera->bindCamera();


    pInstructionUI = InstructionUI::getInstance();
    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, pInstructionUI);

    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuRecordButton);
    //pEngine->storeObjectInArray(++iCurrentGameObject, m_pMenuQuitButton);
    //std::cout << "onActivate done" << std::endl;
}

//int testInt = 2147483647;
void IntroScene::virtMainLoopPreUpdate() {
    //std::cout << "virtMainLoopPreUpdate" << std::endl;
    //std::cout << testInt / 1000 /60  << std::endl;
    pEngine->redrawDisplay();
    /*   if (m_pDiscardButton->isClicked()) {
           SceneStateMachine::getInstance()->switchTo(SceneID::MENU);
       }*/


}

void IntroScene::virtMainLoopDoBeforeUpdate() {
    pViewCamera->onUpdate();
}


void IntroScene::virtPreDraw() {
    pEngine->fillBackground(0x222222);
   
}

void IntroScene::virtPostDraw() {
   /* char buf[128][5];
    sprintf(buf[0], "Mouse X: %2d, Y: %2d", pEngine->getCurrentMouseX(), pEngine->getCurrentMouseY());
    pEngine->drawForegroundString(pViewCamera->getScreenX(20), pViewCamera->getScreenY(100), buf[0], 0x555555, pEngine->getFont("assets/fonts/PixelFont.ttf", 16));

    sprintf(buf[1], "Offset X: %2d, Y: %2d", pViewCamera->getOffset().x, pViewCamera->getOffset().y);
    pEngine->drawForegroundString(pViewCamera->getScreenX(20), pViewCamera->getScreenY(130), buf[1], 0x555555, pEngine->getFont("assets/fonts/PixelFont.ttf", 16));

    sprintf(buf[2], "Zoom Factor X: %2d", pViewCamera->getFactor());
    pEngine->drawForegroundString(pViewCamera->getScreenX(20), pViewCamera->getScreenY(150), buf[2], 0x555555, pEngine->getFont("assets/fonts/PixelFont.ttf", 16));

    sprintf(buf[3], "Camera Pos X: %2d, Y: %2d", pViewCamera->getCameraPosition().x, pViewCamera->getCameraPosition().y);
    pEngine->drawForegroundString(pViewCamera->getScreenX(20), pViewCamera->getScreenY(170), buf[3], 0x555555, pEngine->getFont("assets/fonts/PixelFont.ttf", 16));*/

    //m_pMenuButtonMap->drawAllTiles(pEngine, pEngine->getForegroundSurface());
}

//void IntroScene::virtMouseDown(int iButton, int iX, int iY) {
//   /* if (iButton == SDL_BUTTON_LEFT) {
//        std::cout << "virtMainLoopPreUpdate" << std::endl;
//        pViewCamera->setStart(iX, iY);
//    }*/
//}
//
//void IntroScene::virtMouseUp(int iButton, int iX, int iY) {
//    //if (iButton == SDL_BUTTON_LEFT) {
//    //    pViewCamera->unset();
//    //}
//}

void IntroScene::virtKeyDown(int iKeyCode) {
    if (iKeyCode == SDLK_ESCAPE) {
        SceneStateMachine::getInstance()->switchTo(SceneID::MENU); 
    }
    if (iKeyCode == SDLK_w) {
        pViewCamera->zoomIn();
    }
    else if (iKeyCode == SDLK_s) {
        pViewCamera->zoomOut();
    }
    else if (iKeyCode == SDLK_SPACE) {
        pViewCamera->resetFactor();
        pInstructionUI->resetBG();
    }
}

void IntroScene::onDeactivate() {
    delete pViewCamera;
    pViewCamera = nullptr;
}

void IntroScene::onDestroy() {
    delete pViewCamera;
}
