#pragma once

#include "Utils.h"
#include "ExampleFilterPointClasses.h"

class Zy21586Engine;
class GameObject;
class CaveGenerator;

class GameCamera
{
protected:
    explicit GameCamera();
    static GameCamera* pCamera;

    //Wand* m_pWand{nullptr};
public:
    static GameCamera* getInstance();

private:
    //Vec2 m_oCemeraSize{ 800,800 };
    Vec2 m_oCameraOffset{ 0,0 };
    Vec2 m_oCameraPosition{ 0,0 };

    //Player* m_pPlayer{ nullptr };
    FilterPointsScaling m_filterScaling;
    FilterPointsTranslation m_filterTranslation;

    bool m_bIsCameraShaking{ false };
    //int iCurrentCameraTop{ 0 };
    //int iCurrentCameraBottom{ 0 };
    //int iCurrentCameraLeft{ 0 };
    //int iCurrentCameraRight{ 0 };

public:

    CaveGenerator* m_pCaveMap{ nullptr };

    ~GameCamera();

    void bindCamera();
    void follow(GameObject* pGameObject);

    int getScreenX(int x) { return x - getOffset().x; };
    int getScreenY(int y) { return y - getOffset().y; };
    
    bool IsCameraShaking() { return m_bIsCameraShaking; };
    void shake(bool b) { m_bIsCameraShaking = b; };

    Vec2 getOffset();
    Vec2 getCameraPosition();
   /* int getCurrentCameraTop() { return iCurrentCameraTop; };
    int getCurrentCameraBottom() { return iCurrentCameraBottom; };
    int getCurrentCameraLeft() { return iCurrentCameraLeft; };
    int getCurrentCameraRight() { return iCurrentCameraRight; };*/
};