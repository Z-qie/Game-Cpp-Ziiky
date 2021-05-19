#pragma once

#include "header.h"
#include "SceneBG.h"
#include "SceneStateMachine.h"
#include "ImagePixelMapping.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "Animation.h"

// constructor
SceneBG::SceneBG()
    : GameObject(base_window_width, base_window_height)
    , m_pAnimator(new Animator<SceneID>())
{
    setVisible(true);
    virtStart();
}

// destructor
SceneBG::~SceneBG() {
    delete m_pAnimator;
}

void SceneBG::virtStart() {
    std::shared_ptr<Animation> pMenuSceneAnimtion = std::make_shared<Animation>(300);

    pMenuSceneAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BG_01.png", true, true));
    pMenuSceneAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BG_02.png", true, true));
   
    m_pAnimator->addAnimation(SceneID::MENU, pMenuSceneAnimtion);
}


void SceneBG::virtDoUpdate(int iCurrentTime) {
    m_pAnimator->setAnimationState(SceneStateMachine::getInstance()->getCurrentSceneID());
    redrawDisplay();
}

void SceneBG::virtDraw() {
    if (!isVisible()) return;
    drawSprite();
}


void SceneBG::drawSprite() {
    sprite = m_pAnimator->play();
    //m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));

    //The x and y locationand the widthand height on the surface to draw to
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getBackgroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2,
        m_iCurrentScreenY - sprite.getHeight() / 2,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);
}