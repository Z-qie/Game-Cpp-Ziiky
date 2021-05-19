
#pragma once
#include <vector>

#include "header.h"
#include "GameScene.h"
#include "DisplayableObject.h"
#include "ImagePixelMapping.h"
#include "ImageManager.h"
#include "TileManager.h"
#include "Zy21586Engine.h"
#include "Wand.h"
#include "ThunderZone.h"
#include "Player.h"
#include "Gallo.h"
#include "EnemySpawner.h"
#include "Rune.h"
#include "RuneManager.h"
#include "CaveGenerator.h"
#include "GroundRenderer.h"
#include "DeadWallSpawner.h"
#include "ThunderZone.h"
#include "GameUI.h"
#include "PauseUI.h"
#include "GameOverUI.h"
#include "WinUI.h"
#include "RecordManager.h"
#include "CaveGenerator.h"

void GameScene::onCreate() {
    pEngine = Zy21586Engine::getInstance();
}

void GameScene::onActivate() {
    pEngine->drawableObjectsChanged();
    pEngine->destroyOldObjects(true);	// Destroy any existing objects
    pEngine->notifyObjectsAboutMouse(true);

    pRuneManager = RuneManager::getInstance();
    pCaveGenerator = CaveGenerator::getInstance();
    pGroundRenderer = GroundRenderer::getInstance();
    pDeadWallSpawner = DeadWallSpawner::getInstance();
    pEnemySpawner = EnemySpawner::getInstance();

    pCaveGenerator->generateCave(); // will not be here
    pRuneManager->setTotalRuneNum();
    pDeadWallSpawner->generateCreature();
    pGroundRenderer->randomFillSprite();

    pGameUI = GameUI::getInstance();
    pPauseUI = PauseUI::getInstance();
    pGameOverUI = GameOverUI::getInstance();
    pWinUI = WinUI::getInstance();
    pCamera = GameCamera::getInstance();
    pCamera->bindCamera();

    pPlayer = Player::getInstance();
    pPlayer->setPosition(pCaveGenerator->initPlayerPosition()); // find an empty slot for player's initial position


    Wand* pWand = new Wand();
    ThunderZone* pThunderZone = new ThunderZone();

    int iCurrentGameObject = 0;
    int iGameObjectNum = 100;

    pEngine->createObjectArray(iGameObjectNum);
    pEngine->storeObjectInArray(++iCurrentGameObject, pPlayer);
    for (Gallo* pGallo : pEnemySpawner->getGallos())
        pEngine->storeObjectInArray(++iCurrentGameObject, pGallo);
    pEngine->storeObjectInArray(++iCurrentGameObject, pWand);
    pEngine->storeObjectInArray(++iCurrentGameObject, pThunderZone);
    for (Rune* pRune : pRuneManager->getRunes())
        pEngine->storeObjectInArray(++iCurrentGameObject, pRune);
    pEngine->storeObjectInArray(++iCurrentGameObject, pGameUI);

    //storeObjectInArray(2, m_pTestGallo);//memory leak!!!!!!!
    m_bLose = false;
    m_bWin = false;
}

void GameScene::virtMainLoopPreUpdate() {
    if (pPlayer->isDead()) {
        // pause Gaming 
        if (!pEngine->isPaused())
            pEngine->pause();
        // update inner state
        m_bLose = true;
        m_bWin = false;
    }
    else if (pRuneManager->isAllRuneActivated()) {
        //else if (pRuneManager->getCurrentRuneNum() == 1) {
            // update reocrd
        RecordManager::getInstance()->updateInGameData(
            pGameUI->getSurvivingTimeInSec(),
            pRuneManager->getCurrentRuneNum(),
            pGameUI->getNumOfKill(),
            pGameUI->getCurrentHP());
        // pause Gaming 
        if (!pEngine->isPaused())
            pEngine->pause();
        // update inner state
        m_bLose = false;
        m_bWin = true;
    }
}

void GameScene::virtMainLoopPostUpdate() {
    //a
}

void GameScene::virtMainLoopDoBeforeUpdate() {
 /*   std::list<Rune*>runeList = pRuneManager->getRunes();
    std::list<Rune*>::iterator itrRune = runeList.begin();
    while (itrRune != runeList.end())
    {
        if ((*itrRune)->getState() == RuneState::RUNE_ACTIVE) {
            std::cout << "Rune erasion start:" << (*itrRune)->getPosition().x << ", " << (*itrRune)->getPosition().y << std::endl;
            pEngine->removeDisplayableObject(*itrRune);
            delete* itrRune;
            *itrRune = nullptr;

            itrRune = runeList.erase(itrRune);
        }
        else
            ++itrRune;
    }*/
    std::vector<Rune*>runeList = pRuneManager->getRunes();

    for (int i = 0; i < runeList.size(); i++) {
        Rune* pRune = runeList[i];
        if (/*runeList[i] != nullptr && */pRune->getState() == RuneState::RUNE_ACTIVE) {
            //std::cout << "Rune erasion start:" << pRune->getPosition().x << ", " << pRune->getPosition().y << std::endl;
            if (pEngine->removeDisplayableObject(pRune)) {
                runeList[i] = nullptr;
                delete pRune;
            }
        }
    }


    if (!pEngine->isPaused() /*&& !m_bWin*/) {
        pEnemySpawner->spawnGallos();
    }
    else {

    }
}

void GameScene::virtMainLoopDoAfterUpdate() {
    if (!pEngine->isPaused()/* && !m_bWin*/) {
        pCamera->follow(pPlayer);
        pDeadWallSpawner->updateDeadWall();
        //m_ParticleMap.updateParticleMap();
    }
}

void GameScene::virtPreDraw() {
    if (!pEngine->isPaused()/* && !m_bWin*/) {
        pEngine->fillBackground(0x565656);

        //enhance performance!!!!
        pGroundRenderer->drawAllTiles(pEngine, pEngine->getBackgroundSurface());
        pCaveGenerator->drawAllTiles(pEngine, pEngine->getBackgroundSurface()); // draw cave background
        //should be tile index 
       /* pGroundRenderer->drawSomeTiles(pEngine, pEngine->getBackgroundSurface(), 
            pPlayer->getPosition().x - base_window_width/2, 
            pPlayer->getPosition().y - base_window_height / 2,
            base_window_width,
            base_window_height);
        pCaveGenerator->drawSomeTiles(pEngine, pEngine->getBackgroundSurface(),
            pPlayer->getPosition().x - base_window_width / 2,
            pPlayer->getPosition().y - base_window_height / 2,
            base_window_width,
            base_window_height);*/

    }
}

void GameScene::virtDrawStringsUnderneath() {
}

void GameScene::virtDrawStringsOnTop() {
}

void GameScene::virtPostDraw() {
    pDeadWallSpawner->drawAllTiles(pEngine, pEngine->getForegroundSurface()); // draw dead wall enemy
    pGameUI->drawUI(); // to make sure UI is above everthing.
    //enableDebug();

    if (m_bLose)
    {
        pGameOverUI->drawUI();
    }
    else if (m_bWin) {
        pWinUI->drawUI();
    }
    else {
        pPauseUI->drawUI();
    }

}

void GameScene::onDeactivate() {
    delete pRuneManager;
    delete pCaveGenerator;
    delete pGroundRenderer;
    delete pDeadWallSpawner;
    delete pEnemySpawner;
    delete pCamera;
    delete pPauseUI;
    delete pWinUI;
    delete pGameOverUI;
    // in case user force shut down the game
    pRuneManager = nullptr;
    pCaveGenerator = nullptr;
    pGroundRenderer = nullptr;
    pDeadWallSpawner = nullptr;
    pEnemySpawner = nullptr;
    pCamera = nullptr;
    pPauseUI = nullptr;
    pWinUI = nullptr;
    pGameOverUI = nullptr;

}

void GameScene::onDestroy() {
    delete pRuneManager;
    delete pCaveGenerator;
    delete pGroundRenderer;
    delete pDeadWallSpawner;
    delete pEnemySpawner;
    delete pCamera;
    delete pPauseUI;
    delete pWinUI;
    delete pGameOverUI;
    std::cout << "gamescene destroy done" << std::endl;
}


void GameScene::virtKeyDown(int iKeyCode) {
    switch (iKeyCode)
    {
    case SDLK_SPACE:
        //m_oCaveGenerator.generateCave();
        //m_oCaveGenerator.drawAllTiles(this, getBackgroundSurface());
        if (pEngine->isPaused() && !m_bLose && !m_bWin) // gaming pause
            pEngine->unpause();
        else if (pEngine->isPaused() && m_bLose) { // game over
            CaveGenerator::setSeed();// set random seed of CaveGenerator
            SceneStateMachine::getInstance()->switchTo(SceneID::LOADING);//to be loading
            pEngine->unpause();
        }
        else if (pEngine->isPaused() && m_bWin) { // win
            SceneStateMachine::getInstance()->switchTo(SceneID::RESULT); //RESULT
            pEngine->unpause();
        }
        else if (!pEngine->isPaused() /*&& !m_bWin*/) {
            pEngine->pause();
        }
        break;

    case SDLK_o:
        pRuneManager->activeAllRunes(); // test
        break;
    case SDLK_p:
        //m_oCaveGenerator.smoothMap(); // test
        break;
    case SDLK_ESCAPE:
        // only go back to menu scene by pause UI
        if (pEngine->isPaused() && !m_bWin) {
            SceneStateMachine::getInstance()->switchTo(SceneID::MENU);
            pEngine->unpause();
        }
        break;
    }
}
