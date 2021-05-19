#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "GameObject.h"
#include "WandController.h"
#include "Wand.h"
#include "Projectile.h"
#include "Player.h"

//#include "Collidable.h"


Wand::Wand(int iSize)
    : GameObject(iSize, iSize, 0, 0)
    , m_pAnimator(std::make_unique<Animator<WandState>>())
    , m_pWandController(new WandController(this))
{
    setVisible(true);
    virtStart();
}


void Wand::virtStart() {
    std::shared_ptr<Animation> pWandIdleAnimation = std::make_shared<Animation>(400);
    std::shared_ptr<Animation> pMagicShootAnimation = std::make_shared<Animation>(400);

    pWandIdleAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WAND_01.png", true, true));
    pWandIdleAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WAND_02.png", true, true));
    pMagicShootAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WAND_01.png", true, true));
    pMagicShootAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/WAND_02.png", true, true));

    m_pAnimator->addAnimation(WandState::WAND_IDLE, pWandIdleAnimation);
    m_pAnimator->addAnimation(WandState::WAND_MAGICSHOOT, pMagicShootAnimation);
}


void Wand::virtDraw() {
    //test wand position
    //std::cout << "drawSprite start" << std::endl;
    drawSprite();

}

void Wand::virtDoUpdate(int iCurrentTime) {
    Player* pPlayer = Player::getInstance();
    if (!m_pEngine->isPaused() && !pPlayer->isDead())
    {
        setPosition(pPlayer->getPosition() + utils_rotate_by_centre(Vec2{ 0,0 }, m_oOffsetToPlayer, pPlayer->getAngle()));


        //wandState = WandState::WAND_IDLE;
        m_pWandController->castSpell(); // maybe if statement needed to enhance performance?
        m_pAnimator->setAnimationState(wandState);

        updateAllProjectiles();
    }
    redrawDisplay();
}

long Wand::virtNotify(int iSignalNumber, int x, int y) {
    return 0;
}

void Wand::virtMouseUp(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_LEFT && !m_pEngine->isPaused())
    {
        wandState = WAND_IDLE;
    }
}

void Wand::virtMouseDown(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_LEFT && !m_pEngine->isPaused())
    {
        wandState = WAND_MAGICSHOOT;
    }
}

void Wand::drawSprite() {
    //std::cout << "wand animation play" << std::endl;
    sprite = m_pAnimator->play();
    //std::cout << "wand animation done" << std::endl;

    m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getForegroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2,
        m_iCurrentScreenY - sprite.getHeight() / 2,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping
    );

    //std::cout << "drawAllProjectiles start" << std::endl;

    drawAllProjectiles();

    //std::cout << "drawAllProjectiles done" << std::endl;

}

void Wand::generateProjectileTo(const Vec2& target) {
    m_oProjectileList.push_back(std::make_shared<Projectile>(this->getPosition(), target)); // need to delete
}

void Wand::updateAllProjectiles() {
    std::list<std::shared_ptr<Projectile>>::iterator itrProjectile = m_oProjectileList.begin();
    while (itrProjectile != m_oProjectileList.end())
    {
        if (!(*itrProjectile)->fly()) // if doesn;t collide with anything, then fly
        { // if connot fly anymore(out of screen/out of range) destroy projectile here
            m_oProjectileList.erase(itrProjectile++);  // alternatively, i = items.erase(i);
            //std::cout << "itrProjectile erase" << std::endl;
        }
        else
        {// check next projectile
            ++itrProjectile;
        }
    }
}

void Wand::drawAllProjectiles() {

    for (const std::shared_ptr<Projectile>& pProjectile : m_oProjectileList) {
        int innerOffset = 0;
        int iRadius = 0;

        if (pProjectile->projectileState == ProjectileState::PROJECTILE_FLY) {
            iRadius = pProjectile->getEffectRadiusFly();
            innerOffset = 1;
        }
        else if (pProjectile->projectileState == ProjectileState::PROJECTILE_HIT)
        {
            iRadius = pProjectile->getEffectRadiusHit();
            innerOffset = 5;
        }

        //procedural animation.....tested for a thousand times...
        m_pEngine->drawForegroundOval(
            pProjectile->getPosition().x + iRadius,
            pProjectile->getPosition().y + iRadius,
            pProjectile->getPosition().x - iRadius,
            pProjectile->getPosition().y - iRadius,
            0x9cf5ff);

        m_pEngine->drawForegroundOval( // shadowing!!!!!!!!!!!!!!!!!!!!
            pProjectile->getPosition().x + iRadius + utils_rand(-innerOffset, innerOffset),
            pProjectile->getPosition().y + iRadius + utils_rand(-innerOffset, innerOffset),
            pProjectile->getPosition().x - iRadius + utils_rand(-innerOffset, innerOffset),
            pProjectile->getPosition().y - iRadius + utils_rand(-innerOffset, innerOffset),
            0xececec);
    }
}