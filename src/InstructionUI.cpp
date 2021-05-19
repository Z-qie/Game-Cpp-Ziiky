#pragma once

#include "header.h"
#include "InstructionUI.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "ViewCamera.h"

InstructionUI* InstructionUI::pInstructionUI = nullptr;


InstructionUI* InstructionUI::getInstance()
{
    if (pInstructionUI == nullptr) {
        pInstructionUI = new InstructionUI();
    }
    return pInstructionUI;
}

// constructor
InstructionUI::InstructionUI()
    : GameObject(1440, 2352)
    , m_pAnimator(new Animator<InstructionUIState>())
{
    setVisible(true);
    pCamera = ViewCamera::getInstance();
    virtStart();
}


void InstructionUI::virtStart() {
    std::shared_ptr<Animation> pAnimation = std::make_shared<Animation>(300);

    pAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/INSTRUCTION_01.png", true, true));
    pAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/INSTRUCTION_02.png", true, true));

    m_pAnimator->addAnimation(InstructionUIState::INTRO_IDLE, pAnimation);
    m_pAnimator->setAnimationState(InstructionUIState::INTRO_IDLE);
    setPosition(Vec2{ 720, 2352/2 });
}

void InstructionUI::virtDoUpdate(int iCurrentTime) {
    redrawDisplay();
    sprite = m_pAnimator->play();

   
}


void InstructionUI::virtDraw() {
    if (!isVisible()) return;

    drawSprite();
    drawZoomAlert();
    drawReturnButton();
    drawInstructionMsg();
}

void  InstructionUI::drawSprite() {
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getBackgroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2, // x
        m_iCurrentScreenY - sprite.getHeight() / 2, // y
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);
}

void InstructionUI::drawZoomAlert() {

    if (pCamera->isZoomMax()) {
        m_pEngine->drawForegroundString(
            m_pEngine->convertClickedToVirtualPixelXPosition(300 + utils_rand(-1, 1)), // x
            m_pEngine->convertClickedToVirtualPixelYPosition(6 + utils_rand(-1, 1)), // y
            "ZOOM MAX",
            0xe7fbff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf",
                pCamera->getFactor() > 0 ?
                60 / (pCamera->getFactor() + 1) : 60 * (-pCamera->getFactor() + 1))
        );
    }
    else if (pCamera->isZoomMin()) {
        m_pEngine->drawForegroundString(
            m_pEngine->convertClickedToVirtualPixelXPosition(300 + utils_rand(-1, 1)), // x
            m_pEngine->convertClickedToVirtualPixelYPosition(6 + utils_rand(-1, 1)), // y
            "ZOOM MIN",
            0xe7fbff,
            m_pEngine->getFont("assets/fonts/AmaticRegular.ttf",
                pCamera->getFactor() > 0 ?
                60 / (pCamera->getFactor() + 1) : 60 * (-pCamera->getFactor() + 1))
        );
    }
}

void InstructionUI::drawReturnButton() {
    m_pEngine->drawForegroundString(
        m_pEngine->convertClickedToVirtualPixelXPosition(10 + utils_rand(-1, 1)), // x
        m_pEngine->convertClickedToVirtualPixelYPosition(6 + utils_rand(-1, 1)), // y
        "MENU : ESC",
        0xe7fbff,
        m_pEngine->getFont("assets/fonts/AmaticRegular.ttf",
            pCamera->getFactor() > 0 ?
            40 / (pCamera->getFactor() + 1) : 40 * (-pCamera->getFactor() + 1))
    );
}

void InstructionUI::drawInstructionMsg() {
    m_pEngine->drawForegroundString(
        m_pEngine->convertClickedToVirtualPixelXPosition(55 + utils_rand(-1, 1)), // x
        m_pEngine->convertClickedToVirtualPixelYPosition(650 + utils_rand(-1, 1)), // y
        "-- w : zoom, s : shrink, space : reset, mouse : drag --",
        0xe7fbff,
        m_pEngine->getFont("assets/fonts/AmaticRegular.ttf",
            pCamera->getFactor() > 0 ?
            40 / (pCamera->getFactor() + 1) : 40 * (-pCamera->getFactor() + 1))
    );
}


void InstructionUI::resetBG() {
    // reset pic's position
    setPosition(Vec2{ sprite.getWidth() / 2, sprite.getHeight() / 2 });
}


void InstructionUI::virtMouseDown(int iButton, int iX, int iY)
{
    // handle drag
    if (virtIsPositionWithinObject(iX, iY))
    {
        m_bIsBeingDragged = true;
        m_iInitialClickedDragX = iX;
        m_iInitialClickedDragY = iY;
        m_iStartOfDragX = m_iCurrentScreenX;
        m_iStartOfDragY = m_iCurrentScreenY;
    }
}

void InstructionUI::virtMouseMoved(int iX, int iY)
{
    if (m_bIsBeingDragged)
    {
        m_iCurrentScreenX = m_iStartOfDragX + iX - m_iInitialClickedDragX;
        m_iCurrentScreenY = m_iStartOfDragY + iY - m_iInitialClickedDragY;
        redrawDisplay(); // It moved so do a redraw!
    }
}

/* Override if necessary - Mouse event - mouse button released. Must call notifyObjectsAboutMouse to tell base engine to notify objects, or this will not be called */
void InstructionUI::virtMouseUp(int iButton, int iX, int iY)
{
    m_bIsBeingDragged = false;
}