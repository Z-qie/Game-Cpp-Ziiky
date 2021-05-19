
#pragma once

#include "header.h"
#include "ViewCamera.h"
#include "Zy21586Engine.h"
#include "Utils.h"


ViewCamera* ViewCamera::pViewCamera = nullptr;

ViewCamera* ViewCamera::getInstance()
{
    if (pViewCamera == nullptr) {
        pViewCamera = new ViewCamera();
    }
    return pViewCamera;
}

ViewCamera::ViewCamera()
    : m_pEngine(Zy21586Engine::getInstance())
    , m_filterScaling(0, 0, Zy21586Engine::getInstance())
{
}

ViewCamera ::~ViewCamera()
{
    pViewCamera = nullptr;

    m_pEngine->getBackgroundSurface()->setDrawPointsFilter(Zy21586Engine::getInstance());
    m_pEngine->getForegroundSurface()->setDrawPointsFilter(Zy21586Engine::getInstance());
    Zy21586Engine::getInstance()->getBackgroundSurface()->
        addBoundsCheck(0, base_window_height, 0, base_window_width);
    Zy21586Engine::getInstance()->getForegroundSurface()->
        addBoundsCheck(0, base_window_height, 0, base_window_width);
}

void ViewCamera::bindCamera() {

    m_pEngine->getBackgroundSurface()->setDrawPointsFilter(&m_filterScaling);
    m_pEngine->getForegroundSurface()->setDrawPointsFilter(&m_filterScaling);

}

void ViewCamera::onUpdate() {
    m_filterScaling.setStretch(m_iFactor, m_iFactor);
}

void  ViewCamera::zoomIn() {
    if (m_iFactor < m_iZoomMax)
        ++m_iFactor;
};
void  ViewCamera::zoomOut() {
    if (m_iFactor > m_iZoomMin)
        --m_iFactor;
};
int ViewCamera::getFactor() {
    return m_iFactor;
}

Vec2 ViewCamera::getOffset() {
    return m_oCameraOffset;
}

Vec2 ViewCamera::getCameraPosition() {
    return m_oCameraPosition;
}