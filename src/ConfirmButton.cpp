#pragma once

#include "header.h"
#include "ConfirmButton.h"
#include "ImagePixelMapping.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "Animation.h"
#include "ResultUI.h"
#include "SceneStateMachine.h"

ConfirmButton* ConfirmButton::pConfirmButton = nullptr;

ConfirmButton* ConfirmButton::getInstance()
{
    if (pConfirmButton == nullptr) {
        pConfirmButton = new ConfirmButton();
    }
    return pConfirmButton;
}

// constructor
ConfirmButton::ConfirmButton(int iWidth, int iHeight, int iStartX, int iStartY)
    : BaseButton(iWidth, iHeight, iStartX, iStartY)
{
    m_pAnimator = new Animator<ButtonState>();
    setVisible(true);
    virtStart();
}

// destructor
ConfirmButton::~ConfirmButton() {
    pConfirmButton = nullptr;
}

void ConfirmButton::virtStart() {
    std::shared_ptr<Animation> pButtonIdleAnimtion = std::make_shared<Animation>(150);
    std::shared_ptr<Animation> pButtonHoverAnimtion = std::make_shared<Animation>(150);

    pButtonIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BUTTON_03.png", true, true));

    pButtonHoverAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BUTTON_01.png", true, true));
    pButtonHoverAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BUTTON_02.png", true, true));
    pButtonHoverAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/MENU_BUTTON_03.png", true, true));

    m_pAnimator->addAnimation(ButtonState::BUTTON_IDLE, pButtonIdleAnimtion);
    m_pAnimator->addAnimation(ButtonState::BUTTON_HOVER, pButtonHoverAnimtion);
}


void ConfirmButton::virtDoUpdate(int iCurrentTime) {
    // button state will be updated by baseButton class
    m_pAnimator->setAnimationState(buttonState);
    redrawDisplay();
}

void ConfirmButton::virtDraw() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();

    if (!isVisible()) return;
    drawSprite();

    // draw button name
    int shakeOffset = utils_rand(0, 100) < 20 ? utils_rand(-1, 1) : 0;
    pEngine->drawForegroundString(
        m_iCurrentScreenX - 10 + shakeOffset,
        m_iCurrentScreenY - 12,
        "SAVE",
        0x3d3e3e,
        pEngine->getFont("assets/fonts/AmaticBold.ttf", 21)
    );

    if (buttonState == ButtonState::BUTTON_HOVER && ResultUI::getInstance()->getPlayerName() == "") {
        pEngine->drawForegroundString(
            m_iCurrentScreenX - 80 + shakeOffset,
            m_iCurrentScreenY + 30,
            "NAME CANNOT BE EMPTY!",
            0xffffff,
            pEngine->getFont("assets/fonts/PixelFont.ttf", 16)
        );
    }
}

void ConfirmButton::drawSprite() {
    sprite = m_pAnimator->play();

    m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));
    //The x and y locationand the widthand height on the surface to draw to
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getForegroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2,
        m_iCurrentScreenY - sprite.getHeight() / 2,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);
}

void ConfirmButton::onClick() {
    buttonState = ButtonState::BUTTON_CLICK;
}
