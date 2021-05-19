#pragma once

#include "header.h"
#include "Player.h"
#include "Rune.h"
#include "Zy21586Engine.h"
#include "Animator.h"
#include "Animation.h"
#include "CollisionSystem.h"
#include "RuneManager.h"
#include "EnemySpawner.h"
#include "Gallo.h"
#include "ThunderBolt.h"
#include "GameCamera.h"

const int Rune::iDetectRadius = 30;
const int Rune::iDamage = 250;
const float Rune::fThunderZoneRadius = 350.f;

Rune::Rune(int x, int y)
    :GameObject(0, 0, 0, 0)
    , m_pAnimator(new Animator<RuneState>())

{
    // need to reset the position becasuse the garbage base obeject fix it position!!!
    setPosition(Vec2{ x,y });
    setVisible(true);
    virtStart();
}

Rune::~Rune() {
    delete m_pAnimator;
};

void Rune::virtStart() {
    std::shared_ptr<Animation> pRuneIdleAnimtion = std::make_shared<Animation>(200);
    std::shared_ptr<Animation> pRuneActivatingAnimtion = std::make_shared<Animation>(200);
    std::shared_ptr<Animation> pRuneActiveAnimtion = std::make_shared<Animation>(200);

    pRuneIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_IDLE_01.png", true, true));
    pRuneIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_IDLE_02.png", true, true));
    pRuneIdleAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_IDLE_03.png", true, true));

    pRuneActiveAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/THUNDER_BOLT_01.png", true, true));
    pRuneActiveAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/THUNDER_BOLT_02.png", true, true));

    pRuneActivatingAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_ACTIVE_01.png", true, true));
    pRuneActivatingAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_ACTIVE_02.png", true, true));
    pRuneActivatingAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_ACTIVE_03.png", true, true));
    pRuneActivatingAnimtion->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/RUNE_ACTIVE_04.png", true, true));

    m_pAnimator->addAnimation(RuneState::RUNE_IDLE, pRuneIdleAnimtion);
    m_pAnimator->addAnimation(RuneState::RUNE_ACTIVATING, pRuneActivatingAnimtion);
    m_pAnimator->addAnimation(RuneState::RUNE_ACTIVE, pRuneActiveAnimtion);
}

void Rune::virtDraw() {
    if (!isVisible())
        return;
    drawSprite();
}

void Rune::virtDoUpdate(int iCurrentTime) {
    Vec2 playerPos = Player::getInstance()->getPosition();

    if (CollisionSystem::checkCircles(getPosition().x, getPosition().y, playerPos.x, playerPos.y, iDetectRadius)) {
        if (runeState == RuneState::RUNE_IDLE) {
            runeState = RuneState::RUNE_ACTIVATING;
            m_iStartActiveTime = iCurrentTime;
            RuneManager::getInstance()->incrementActiveRuneNum();
        }
    }

    if (runeState == RuneState::RUNE_ACTIVATING) {
        GameCamera::getInstance()->shake(true);
        if (m_iActivingRemainTime > iCurrentTime - m_iStartActiveTime) {
            castSpell(); // maybe if statement needed to enhance performance?
        }
        else if (m_iActiveRemainTime < iCurrentTime - m_iStartActiveTime) {
            runeState = RuneState::RUNE_ACTIVE;
            GameCamera::getInstance()->shake(false);  // stop shake camera
            return;
        }
        else {
            GameCamera::getInstance()->shake(false);  // stop shake camera
        }
    }

    updateAllThunderBolts();
    m_pAnimator->setAnimationState(runeState);
    redrawDisplay();
}

void Rune::drawSprite() {
    sprite = m_pAnimator->play();
    m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));
    sprite.renderImageApplyingMapping(
        m_pEngine,
        m_pEngine->getForegroundSurface(),
        m_iCurrentScreenX - sprite.getWidth() / 2,
        m_iCurrentScreenY - sprite.getHeight() / 2,
        sprite.getWidth(),
        sprite.getHeight(),
        m_pSpriteMapping);
    drawAllThunderBolts();

}

void Rune::castSpell() {
    //Player* pPlayer = Player::getInstance();

    // to be generic!!!!!
    std::vector<Gallo*>gallos = EnemySpawner::getInstance()->getGallos();
    for (Gallo* pGallo : gallos) {
        if (CollisionSystem::checkCircles(
            getPosition().x,
            getPosition().y,
            pGallo->getPosition().x,
            pGallo->getPosition().y,
            static_cast<int>(fThunderZoneRadius))
            && !(pGallo->getGalloState() == GalloState::GALLO_INACTIVE)
            && !pGallo->isTakingThunder()) { // if the enemy is active and not taking thunder, taking hit
            pGallo->setTakingThunder(true);
            if (!(pGallo->getGalloState() == GalloState::GALLO_ONDEATH)) // remain effect but only take damge once
                pGallo->takeHit(iDamage); // damage enemy
            castThunderBoltAt(pGallo->getPosition()); // cast bolt
            return;
        }
    }

    for (Gallo* pGallo : gallos)
        pGallo->setTakingThunder(false); // set back to make sure next thunder can hit on !!!!!!!!!!!!!!!!

}

void Rune::castThunderBoltAt(const Vec2& target) {
    m_oThunderBoltList.push_back(std::make_shared<ThunderBolt>(target, getPosition()));
}


void Rune::updateAllThunderBolts() {
    std::list<std::shared_ptr<ThunderBolt>>::iterator itr = m_oThunderBoltList.begin();
    while (itr != m_oThunderBoltList.end())
    {
        if (!(*itr)->formalizeFlash()) // update form of thunder storm
        {
            m_oThunderBoltList.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }
}

void Rune::drawAllThunderBolts() {

    for (const std::shared_ptr<ThunderBolt>& pBolt : m_oThunderBoltList) {
        if (pBolt->thunderBoltState == ThunderBoltState::THUNDERBOLT_FLASHING) {
            pBolt->thunderBoltState = ThunderBoltState::THUNDERBOLT_INTERVAL;

            // flash bolts
            sprite = m_pAnimator->play();
            const Vec2& target = pBolt->getTarget();
            m_pSpriteMapping->setTransparencyColour(sprite.getPixelColour(0, 0));
            sprite.renderImageApplyingMapping(
                m_pEngine,
                m_pEngine->getForegroundSurface(),
                target.x - sprite.getWidth() / 2,
                target.y - sprite.getHeight() / 2,
                sprite.getWidth(),
                sprite.getHeight(),
                m_pSpriteMapping);



            // flash line
            std::queue<Vec2>& rLine = pBolt->m_oThunderFlashLine;
            Vec2 start = rLine.front();
            rLine.pop();

            while (!rLine.empty())
            {
                Vec2 next = rLine.front();
                m_pEngine->drawBackgroundThickLine(
                    start.x, start.y,
                    next.x, next.y,
                    0xd3f3ff
                    , 3);
                m_pEngine->drawForegroundLine(
                    start.x, start.y,
                    next.x, next.y,
                    0xffffff);

                start = next;
                rLine.pop();
            }
        }
    }
}