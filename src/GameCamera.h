#pragma once

#include "Utils.h"
#include "ExampleFilterPointClasses.h"

class Zy21586Engine;
class GameObject;
class CaveGenerator;

//Camera class containsand handles FilterPoints like scalingand translation added on drawingSurface.
//GameCamera can be bind onto a specific game object(player in this game) and follow the game object 
//while it moves. 
//1. GameCamera will add a strict limit when player approach the boundary of the map, instead of place the player as center,
//it will be restricted by the map boundary
//2. GameCamera can handle simple camera effect like shaking.
class GameCamera
{
protected:
    explicit GameCamera();
    static GameCamera* pCamera;

public:
    static GameCamera* getInstance();

private:
    Vec2 m_oCameraOffset{ 0,0 };
    Vec2 m_oCameraPosition{ 0,0 };

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
    
   /* 
    int getCurrentCameraBottom() { return iCurrentCameraBottom; };
    int getCurrentCameraLeft() { return iCurrentCameraLeft; };
    int getCurrentCameraRight() { return iCurrentCameraRight; };*/
};