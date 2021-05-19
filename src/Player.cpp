#pragma once

#include "header.h"
#include "Player.h"
#include "PlayerController.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "Animation.h"

Player* Player::pPlayer = nullptr;

Player* Player::getInstance()
{
    if (pPlayer == nullptr) {
        pPlayer = new Player();
    }
    return pPlayer;
}

// constructor
Player::Player(int iWidth, int iHeight, int iStartX, int iStartY, int iStartingHealth)
    : LivingEntity(iWidth, iHeight, iStartX, iStartY, iStartingHealth)
    , m_pPlayerController(new PlayerController())
    , m_pAnimator(new Animator<PlayerState>())
{
    setVisible(true);
    virtStart();
    //m_iHealth = 100;//test
}

// destructor
Player::~Player() {
    pPlayer = nullptr;
    delete m_pPlayerController;
    //delete m_pWandController;
    delete m_pAnimator;
    std::cout << "deleteing Player" << std::endl;
}

void Player::virtStart() {
    std::shared_ptr<Animation> pPlayerIdleAnimtion = std::make_shared<Animation>(400);
    std::shared_ptr<Animation> pPlayerRunnLeftAnimtion = std::make_shared<Animation>(400);
    std::shared_ptr<Animation> pPlayerRunnRightAnimtion = std::make_shared<Animation>(400);

    pPlayerIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_IDLE_01.png", true, true));
    pPlayerIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_IDLE_02.png", true, true));
    pPlayerRunnLeftAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_LEFT_01.png", true, true));
    pPlayerRunnLeftAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_LEFT_02.png", true, true));
    pPlayerRunnRightAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_RIGHT_01.png", true, true));
    pPlayerRunnRightAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WITCH_RIGHT_02.png", true, true));

    m_pAnimator->addAnimation(PlayerState::PLAYER_IDLE, pPlayerIdleAnimtion);
    m_pAnimator->addAnimation(PlayerState::PLAYER_RUN_LEFT, pPlayerRunnLeftAnimtion);
    m_pAnimator->addAnimation(PlayerState::PLAYER_RUN_RIGHT, pPlayerRunnRightAnimtion);

    //std::cout << "virtStart" << std::endl;
}


void Player::virtDoUpdate(int iCurrentTime) {
    if (!m_pEngine->isPaused() && !m_bIsDead)
    {
        playerState = m_pPlayerController->move();
        m_pAnimator->setAnimationState(playerState);
        m_pPlayerController->lookAt();
        redrawDisplay();
    }
}

void Player::virtDraw() {
    if (!isVisible()) return;

    drawSprite();
}



void Player::drawSprite() {

    sprite = m_pAnimator->play();

    m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));

    if (m_iHealth < 200) {
        // show the low HP stage in red boold colour
        m_pSpriteMapping->setNthPixelColours(0x4c1d1d, -1, -1);
    }
    
  
    //The xand y locationand the widthand height on the surface to draw to
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getForegroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2,
        m_iCurrentScreenY - sprite.getHeight() / 2,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);

    // procedural animation : effect lerp when taking hit !!!!!!!!!!!!!
    m_pSpriteMapping->setBrightnessPercentage(static_cast<int>(m_fTakeHitEffectLerp = utils_lerp(m_fTakeHitEffectLerp, 100.f, 0.1f)));

    // ray test
    //Vec2 mousePosition{ m_pEngine->getCurrentMouseX(), m_pEngine->getCurrentMouseY() };
    //m_pEngine->drawForegroundLine(m_iCurrentScreenX, m_iCurrentScreenY, mousePosition.x, mousePosition.y, 0xff0000);
}

void Player::takeHit(int damage) {
    m_fTakeHitEffectLerp = 0.f;
    m_pSpriteMapping->setBrightnessPercentage(static_cast<int>(m_fTakeHitEffectLerp));
    LivingEntity::takeHit(damage);
}


void  Player::onDeath() {
    m_iHealth = 0;
    // more effect probly?
};