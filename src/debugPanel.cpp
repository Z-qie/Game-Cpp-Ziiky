#pragma once
#include "header.h"
#include "Zy21586Engine.h"
#include "CaveGenerator.h"
#include "EnemySpawner.h"
#include "Player.h"
#include "Gallo.h"
#include "GameScene.h"


int iRenderLastTime = 0;

void GameScene::enableDebug() {
    char buf[128][10];
    // set time
    sprintf(buf[7], "Frame: %f", 1000 / static_cast<float>(pEngine->getModifiedTime() - iRenderLastTime));
    iRenderLastTime = pEngine->getModifiedTime();
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(20), buf[7], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));
    // set time
    sprintf(buf[0], "Modified Time %6d", pEngine->getModifiedTime());
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(40), buf[0], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

    sprintf(buf[1], "Ticked Time %6d", pEngine->getRawTime());
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(60), buf[1], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

   /* sprintf(buf[2], "Paused Time %6d", pEngine->);
    drawForegroundString(getScreenX(20), getScreenY(80), buf[2], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));*/

    sprintf(buf[3], "Mouse X: %2d, Y: %2d", pEngine->getCurrentMouseX(), pEngine->getCurrentMouseY());
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(100), buf[3], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

    sprintf(buf[5], "Map Current Screen: %2d %2d", pCaveGenerator->m_iBaseScreenX, pCaveGenerator->m_iBaseScreenY);
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(120), buf[5], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

    sprintf(buf[4], "Player Current Screen: %2d %2d", pPlayer->getPosition().x, pPlayer->getPosition().y);
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(140), buf[4], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

    sprintf(buf[6], "Current Gallo Number: %d", pEnemySpawner->getLivingGalloNum());
    pEngine->drawForegroundString(pCamera->getScreenX(20), pCamera->getScreenY(160), buf[6], 0xffffff, pEngine->getFont("assets/fonts/PixelFont.ttf", 12));

}