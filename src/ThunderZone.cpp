
#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "BaseEngine.h"
#include "GameObject.h"
#include "ThunderZoneController.h"
#include "ThunderZone.h"
#include "ThunderBolt.h"
#include "Player.h"
#include "GameCamera.h"


float ThunderZone::fThunderZoneMaxTime = 4000.f; // 5s
float ThunderZone::fThunderZoneRemainTime = 4000.f;
float ThunderZone::fThunderZoneRecoverSpeed = 0.06f;
float ThunderZone::fThunderZoneRadius = 0.f;
float ThunderZone::fThunderZoneRadiusMax = 200.f;
int ThunderZone::iThunderZoneDamage = 1000;


ThunderZone::ThunderZone(int iSize)
    : GameObject(iSize, iSize, 0, 0)
    , m_pAnimator(std::make_unique<Animator<ThunderZoneState>>())
    , m_pThunderZoneController(new ThunderZoneController(this))
{
    setVisible(false);
    virtStart();
}

void ThunderZone::virtStart() {

    fThunderZoneMaxTime = 5000.f; // 5s
    fThunderZoneRemainTime = 5000.f;
    std::shared_ptr<Animation> pFlashAnimation = std::make_shared<Animation>(200);

    pFlashAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/THUNDER_BOLT_01.png", true, true));
    pFlashAnimation->addFrame(ImageManager::get()->getImagebyURL("assets/sprites/THUNDER_BOLT_02.png", true, true));

    m_pAnimator->addAnimation(ThunderZoneState::THUNDER_ACTIVE, pFlashAnimation);
}

void ThunderZone::virtMouseUp(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_RIGHT && !m_pEngine->isPaused())
    {
        if (!(thunderZoneState == ThunderZoneState::THUNDER_COOLDOWN))
            thunderZoneState = ThunderZoneState::THUNDER_IDLE;
    }
}

void ThunderZone::virtMouseDown(int iButton, int iX, int iY) {
    if (iButton == SDL_BUTTON_RIGHT && !m_pEngine->isPaused())
    {
        if (!(thunderZoneState == ThunderZoneState::THUNDER_COOLDOWN))
            thunderZoneState = ThunderZoneState::THUNDER_ACTIVE;
    }
}

void ThunderZone::virtDraw() {
    //test wand position
    //std::cout << "drawSprite start" << std::endl;
    drawSprite();
}


void ThunderZone::virtDoUpdate(int iCurrentTime) {
    Player* pPlayer = Player::getInstance();

    if (!m_pEngine->isPaused() && !pPlayer->isDead())
    {
        setPosition(pPlayer->getPosition());

        // keep resuming energy
        if (fThunderZoneRemainTime < fThunderZoneMaxTime)
            fThunderZoneRemainTime += fThunderZoneRecoverSpeed * (iCurrentTime - m_iLastupdateTime);

        // if casting spell, consume energy
        if (thunderZoneState == ThunderZoneState::THUNDER_ACTIVE) {
            fThunderZoneRemainTime -= iCurrentTime - m_iLastupdateTime;
            if (fThunderZoneRemainTime <= 0) { // if energy is empty, stop
                fThunderZoneRemainTime = 0;
                thunderZoneState = ThunderZoneState::THUNDER_COOLDOWN;
                //iThunderZoneRemainTime = iThunderZoneMaxTime; // reset remaining time
                //iThunderZoneReadyTime = iCurrentTime + iThunderZoneCoolDownTime; // set next ready time
            }
            else {
                m_pThunderZoneController->castSpell(); // maybe if statement needed to enhance performance?
            }
        }
        m_iLastupdateTime = iCurrentTime;

        GameCamera::getInstance()->shake(thunderZoneState == ThunderZoneState::THUNDER_ACTIVE); // shake camera
        updateAllThunderBolts();
        m_pAnimator->setAnimationState(thunderZoneState);
        redrawDisplay();
    }
}

void ThunderZone::drawSprite() {
    int iCurrentTime = Zy21586Engine::getInstance()->getModifiedTime();
    Player* pPlayer = Player::getInstance();

    if (thunderZoneState == ThunderZoneState::THUNDER_ACTIVE) {
        // zoom out
        fThunderZoneRadius = utils_lerp(fThunderZoneRadius, fThunderZoneRadiusMax, 0.1f);
        int radius = static_cast<int>(fThunderZoneRadius);
        m_pEngine->getForegroundSurface()->drawHollowOval(
            pPlayer->getPosition().x + radius,
            pPlayer->getPosition().y + radius,
            pPlayer->getPosition().x - radius,
            pPlayer->getPosition().y - radius,
            pPlayer->getPosition().x + radius + utils_rand(-1, 1),
            pPlayer->getPosition().y + radius + utils_rand(-1, 1),
            pPlayer->getPosition().x - radius + utils_rand(-1, 1),
            pPlayer->getPosition().y - radius + utils_rand(-1, 1),
            utils_rand(0, 3) == 0 ? 0xffffff : 0xd3f3ff);
        drawAllThunderBolts();
    }
    else if (thunderZoneState == ThunderZoneState::THUNDER_COOLDOWN || thunderZoneState == ThunderZoneState::THUNDER_IDLE)
    {   // zoom in
        fThunderZoneRadius = utils_lerp(fThunderZoneRadius, 0, 0.1f);
        int radius = static_cast<int>(fThunderZoneRadius);
        m_pEngine->getForegroundSurface()->drawHollowOval(
            pPlayer->getPosition().x + radius,
            pPlayer->getPosition().y + radius,
            pPlayer->getPosition().x - radius,
            pPlayer->getPosition().y - radius,
            pPlayer->getPosition().x + radius + utils_rand(-1, 1),
            pPlayer->getPosition().y + radius + utils_rand(-1, 1),
            pPlayer->getPosition().x - radius + utils_rand(-1, 1),
            pPlayer->getPosition().y - radius + utils_rand(-1, 1),
            utils_rand(0, 3) == 0 ? 0xffffff : 0xd3f3ff);

        //std::cout << "THUNDER_COOLDOWN start" << std::endl;
        if (thunderZoneState == ThunderZoneState::THUNDER_COOLDOWN) {
            thunderZoneState = ThunderZoneState::THUNDER_IDLE;
        }
    }
}

void ThunderZone::castThunderBoltAt(const Vec2& target) {
    m_oThunderBoltList.push_back(std::make_shared<ThunderBolt>(target)); // need to delete
}


void ThunderZone::updateAllThunderBolts() {
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

void ThunderZone::drawAllThunderBolts() {

    for (const std::shared_ptr<ThunderBolt>& pBolt : m_oThunderBoltList) {
        if (pBolt->thunderBoltState == ThunderBoltState::THUNDERBOLT_FLASHING) {
            pBolt->thunderBoltState = ThunderBoltState::THUNDERBOLT_INTERVAL;

            // flash bolts
            if (thunderZoneState == ThunderZoneState::THUNDER_ACTIVE) {
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
            }


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