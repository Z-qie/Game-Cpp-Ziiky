#pragma once
#include "Utils.h"
#include "ExampleFilterPointClasses.h"
#include "Zy21586FilterPointsScale.h"

class Zy21586Engine;
class GameObject;
class CaveGenerator;

// ViewCamera class contains and handles a Zy21586FilterPointsScale and a FilterPointsTranslation. 
// ViewCamera is used in introScene to zoom and shrink the user manual(Dragable gameobject) 
// by keyboard (w to zoom, s to shrink and space to reset) and mouse (click to drag).
class ViewCamera
{
protected:
    explicit ViewCamera();
    static ViewCamera* pViewCamera;

    //Wand* m_pWand{nullptr};
public:
    static ViewCamera* getInstance();
    ~ViewCamera();

private:
    Zy21586Engine* m_pEngine{ nullptr };
    Vec2 m_oCameraOffset{ -0,-0 };
    Vec2 m_oLastMouseDownPos{ 0,0 };
    Vec2 m_oCameraPosition{ 0,0 };

    int m_iTranslateSpeed{ 15 };
    int m_iFactor{ -1 };
    int m_iZoomMax{ 2 };
    int m_iZoomMin{ -3 };

    Zy21586FilterPointsScale m_filterScaling; 
    FilterPointsTranslation m_filterTranslation;


public:
    void bindCamera();
    void onUpdate();
    int getScreenX(int x) { return x - getOffset().x; };
    int getScreenY(int y) { return y - getOffset().y; };

    void zoomIn();
    void zoomOut();
    int getFactor();
    void resetFactor() { m_iFactor = -1; };

    bool isZoomMax() { return m_iFactor == m_iZoomMax; };
    bool isZoomMin() { return m_iFactor == m_iZoomMin; };
    Vec2 getOffset();
    Vec2 getCameraPosition();
};