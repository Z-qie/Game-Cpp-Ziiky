#pragma once

#include "header.h"
#include "GameCamera.h"
#include "Player.h"
#include "Zy21586Engine.h"
#include "Utils.h"
#include "CaveGenerator.h"

GameCamera* GameCamera::pCamera = nullptr;

GameCamera* GameCamera::getInstance()
{
    if (pCamera == nullptr) {
        pCamera = new GameCamera();
    }
    return pCamera;
}

GameCamera::GameCamera()
    : m_filterScaling(0, 0, Zy21586Engine::getInstance())//fuck this!
    , m_filterTranslation(0, 0, /*&m_filterScaling*/Zy21586Engine::getInstance())
{
}

GameCamera ::~GameCamera()
{
    pCamera = nullptr;
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    pEngine->getBackgroundSurface()->setDrawPointsFilter(Zy21586Engine::getInstance());
    pEngine->getForegroundSurface()->setDrawPointsFilter(Zy21586Engine::getInstance());
    Zy21586Engine::getInstance()->getBackgroundSurface()->
        addBoundsCheck(0, base_window_height, 0, base_window_width);
    Zy21586Engine::getInstance()->getForegroundSurface()->
        addBoundsCheck(0, base_window_height, 0, base_window_width);
}

void GameCamera::bindCamera() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    
    pEngine->getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
    pEngine->getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
}

void GameCamera::follow(GameObject* pGameObject) {
    // set camera offset to follow given GameObject(normally player)
    Vec2 gameObjectPos = pGameObject->getPosition();

    if (m_bIsCameraShaking == true && utils_rand(1, 100) < 30)//30
    {
        int shakeStrength = 10;//20
        m_oCameraOffset = {
            -gameObjectPos.x + base_window_width / 2 + utils_rand(-shakeStrength, shakeStrength),
            -gameObjectPos.y + base_window_height / 2 + utils_rand(-shakeStrength, shakeStrength) };
    }
    else
        m_oCameraOffset = {
            -gameObjectPos.x + base_window_width / 2,
            -gameObjectPos.y + base_window_height / 2 };



    // set camera boundary
    int iCurrentCameraTop = gameObjectPos.y - base_window_height / 2;
    int iCurrentCameraBottom = gameObjectPos.y + base_window_height / 2;
    int iCurrentCameraLeft = gameObjectPos.x - base_window_width / 2;
    int iCurrentCameraRight = gameObjectPos.x + base_window_width / 2;

    // limit the boundary of camera inside the cave tile map!!!
    CaveGenerator* pCave = CaveGenerator::getInstance();
    if (iCurrentCameraLeft <= 0)
        m_oCameraOffset.x = 0;
    if (iCurrentCameraRight >= pCave->getMapWidth() * pCave->getTileWidth())
        m_oCameraOffset.x = base_window_width - pCave->getMapWidth() * pCave->getTileWidth();
    if (iCurrentCameraTop <= 0)
        m_oCameraOffset.y = 0;
    if (iCurrentCameraBottom >= pCave->getMapHeight() * pCave->getTileHeight())
        m_oCameraOffset.y = base_window_height - pCave->getMapHeight() * pCave->getTileHeight();

    m_filterTranslation.setOffset(m_oCameraOffset.x, m_oCameraOffset.y);
    m_oCameraPosition = { base_window_width / 2 - m_oCameraOffset.x, base_window_height / 2 - m_oCameraOffset.y };

    // this can massively reduce overhead of rendering all map!!!!!!!!
    Zy21586Engine::getInstance()->getBackgroundSurface()->
        addBoundsCheck(
            m_oCameraPosition.y - base_window_height / 2,
            m_oCameraPosition.y + base_window_height / 2,
            m_oCameraPosition.x - base_window_width / 2,
            m_oCameraPosition.x + base_window_width / 2);

    Zy21586Engine::getInstance()->getForegroundSurface()->
        addBoundsCheck(
            m_oCameraPosition.y - base_window_height / 2,
            m_oCameraPosition.y + base_window_height / 2,
            m_oCameraPosition.x - base_window_width / 2,
            m_oCameraPosition.x + base_window_width / 2);

    //std::cout << m_oCameraOffset.x << ", " << m_oCameraOffset.y << ", "
    //    << m_oCameraPosition.x << ", " << m_oCameraPosition.y << std::endl;

}

Vec2 GameCamera::getOffset() {
    return m_oCameraOffset;
}

Vec2 GameCamera::getCameraPosition() {
    return m_oCameraPosition;
}