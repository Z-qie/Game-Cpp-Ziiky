#pragma once

#include "header.h"
#include "Gallo.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "Zy21586Engine.h"
#include "EnemySpawner.h"
#include "CaveGenerator.h"
#include "GameUI.h"

int Gallo::iInitGalloHealth{ 1000 };
int Gallo::iMoveSpeed{ 7 };
int Gallo::iPrecisionError{ 5 };

int Gallo::iObstacleRadius{ 20 };
int Gallo::iWanderRadius{ 100 };
int Gallo::iWanderClampValue = iWanderRadius * 4;
int Gallo::iWanderFrequency{ 5000 };
int Gallo::iDetectRadius{ 300 };
int Gallo::iSleepRadius{ 1000 };

int Gallo::iChaseFrequency{ 1000 };
int Gallo::iAttackRadius{ 50 };
int Gallo::iAttackInterval{ 300 };
int Gallo::iDamage{ 30 };

int Gallo::iDeathEffectInterval{ 1500 };


Gallo::Gallo(int iStartX, int iStartY, int iWidth, int iHeight, int iStartingHealth)
    :LivingEntity(iWidth, iHeight, iStartX, iStartY, iStartingHealth)
    , m_oWanderCenter(iStartX, iStartY)
{
    setVisible(false);

    // need to reset the position becasuse the garbage base obeject fix it position!!!
    //setPosition(Vec2{ iStartX,iStartY });
};

void Gallo::virtDoUpdate(int iCurrentTime) {
    //if (m_pEngine->isKeyPressed(SDLK_j))
    //    delete this;
    if (!m_pEngine->isPaused())
    {
        Player* pPlayer = Player::getInstance();

        switch (galloState)
        {
        case GALLO_ONDEATH:
            onDeath();
            break;
        case GALLO_INACTIVE:
            //if (isVisible()) {
            //    EnemySpawner::getInstance()->decrementLivingGallo();
            //    //++EnemykilledNum;
            //    setVisible(false);
            //}

            break;

        case GALLO_WANDER:
        {
            bool foundTarget = CollisionSystem::checkCircles(
                pPlayer->getPosition().x, pPlayer->getPosition().y,
                m_iCurrentScreenX, m_iCurrentScreenY, iDetectRadius);

            if (foundTarget) {
                galloState = GALLO_CHASE;
                chase();
            }
            else
                wander();
        }
        break;

        case GALLO_ATTACK:
        {
            if (m_iAttackEndTime < m_pEngine->getModifiedTime()) {
                m_iAttackEndTime = m_pEngine->getModifiedTime() + iAttackInterval;
                std::cout << ":attacking" << std::endl;
                attack();
            }
            else
                galloState = GALLO_WANDER;
        }
        break;

        case GALLO_CHASE:
        {
            m_bNeedRenderAttack = CollisionSystem::checkCircles(
                pPlayer->getPosition().x, pPlayer->getPosition().y,
                m_iCurrentScreenX, m_iCurrentScreenY, iAttackRadius);
            if (m_bNeedRenderAttack)
                galloState = GALLO_ATTACK;
            else
                galloState = GALLO_WANDER;
        }
        break;
        }
        //galloState = GALLO_WANDER;
        redrawDisplay();
    }
}


void Gallo::wakeUp(Vec2 initialPosition) {
    setPosition(initialPosition);
    m_oWanderCenter = initialPosition;
    m_iHealth = iInitGalloHealth;
    m_bIsDead = false;
    galloState = GALLO_WANDER;
    m_bNeedRenderAttack = false;
    setVisible(true);
}

void Gallo::wander() {
    // check if too far from player, if so
    Vec2 playerPosition = Player::getInstance()->getPosition();
    if (!CollisionSystem::checkCircles(getPosition().x, getPosition().y, playerPosition.x, playerPosition.y, iSleepRadius)) {
        std::cout << "go to sleep" << std::endl;
        sleep();
    }

    CaveGenerator* pCave = CaveGenerator::getInstance();
    int iCurrentTime = m_pEngine->getModifiedTime();
    if (m_iNextValidTime < iCurrentTime)
    {
        m_iNextValidTime = iCurrentTime + iWanderFrequency;
        do {// find a valid position
            m_oNextWanderPosition = { // I use clamp here to keep the random target long enough
                utils_clamp_g(
                    utils_rand(m_oWanderCenter.x - iWanderClampValue, m_oWanderCenter.x + iWanderClampValue),
                    m_oWanderCenter.x - iWanderRadius ,m_oWanderCenter.x + iWanderRadius),
                 utils_clamp_g(
                     utils_rand(m_oWanderCenter.y - iWanderClampValue, m_oWanderCenter.y + iWanderClampValue),
                     m_oWanderCenter.y - iWanderRadius, m_oWanderCenter.y + iWanderRadius) };
        } while (// check the target position is inside the cave and on the ground
            CollisionSystem::checkObstacleBySquare(m_oNextWanderPosition.x, m_oNextWanderPosition.y, iObstacleRadius));
    }

    Vec2 moveVelocity(utils_offset_by_direction(iMoveSpeed, m_oNextWanderPosition - getPosition()));

    // to enhance smooth experience
    if (CollisionSystem::checkObstacleBySquare(moveVelocity.x + getPosition().x, getPosition().y, iObstacleRadius))
        moveVelocity.x = 0;
    if (CollisionSystem::checkObstacleBySquare(getPosition().x, moveVelocity.y + getPosition().y, iObstacleRadius))
        moveVelocity.y = 0;

    if (moveVelocity.x == 0 && moveVelocity.y == 0)
        m_iNextValidTime = 0;
    else
    {   // change direction for rendering
        //galloDir = moveVelocity.y > 0 ? DOWN : UP;
        galloDir = moveVelocity.x > 0 ? RIGHT : LEFT; // ignore virtical if move horizontally

        // move
        translatePositionBy(moveVelocity);

        // ignore the precision hiahiahiahia
        if (CollisionSystem::checkCircles(
            m_oNextWanderPosition.x, m_oNextWanderPosition.y, getPosition().x, getPosition().y, iPrecisionError))
            m_iNextValidTime = 0;
    }
}

void Gallo::chase() {
    // 1. stupid chase
    Vec2 playerPosition = Player::getInstance()->getPosition();
    int iCurrentTime = m_pEngine->getModifiedTime();

    if (m_iNextValidTime < iCurrentTime)
    {// update chasing target at times
        m_iNextValidTime = iCurrentTime + iChaseFrequency;
        m_oNextWanderPosition = { playerPosition.x ,playerPosition.y };
    }

    Vec2 moveVelocity(utils_offset_by_direction(iMoveSpeed, m_oNextWanderPosition - getPosition()));

    // to enhance smooth experience
    if (CollisionSystem::checkObstacleBySquare(moveVelocity.x + getPosition().x, getPosition().y, iObstacleRadius))
        moveVelocity.x = 0;
    if (CollisionSystem::checkObstacleBySquare(getPosition().x, moveVelocity.y + getPosition().y, iObstacleRadius))
        moveVelocity.y = 0;

    if (moveVelocity.x == 0 && moveVelocity.y == 0)
        m_iNextValidTime = 0;
    else
    {  // change direction for rendering
        //galloDir = moveVelocity.y > 0 ? DOWN : UP;
        galloDir = moveVelocity.x > 0 ? RIGHT : LEFT; // ignore virtical if move horizontally
        translatePositionBy(moveVelocity);

        // ignore the precision hiahiahiahia
        if (CollisionSystem::checkCircles(
            m_oNextWanderPosition.x, m_oNextWanderPosition.y, getPosition().x, getPosition().y, iPrecisionError))
            m_iNextValidTime = 0;
    }

    // 2. A* algorithm
    //...later
}

void Gallo::attack() {
    Player::getInstance()->takeHit(iDamage);
}

void Gallo::drawSprite() {
}


void Gallo::onDeath() {
    //isDead = true;//already implement in livingEntity
    int iCurrentTime = m_pEngine->getModifiedTime();
    m_bNeedRenderAttack = false;
    if (m_iDeadthEndTime < iCurrentTime)
    {// update chasing target at times
        m_iDeadthEndTime = iCurrentTime + iDeathEffectInterval;
        if (galloState == GALLO_ONDEATH)
            galloState = GALLO_INACTIVE;
        else {
            galloState = GALLO_ONDEATH;
            return;
        }
    }

    if (galloState == GALLO_INACTIVE) { // really kill the enemy after render death effect
        EnemySpawner::getInstance()->decrementLivingGallo();
        setVisible(false);
        m_iDeadthEndTime = 0;
    }
}

void Gallo::takeHit(int damage) {
    LivingEntity::takeHit(damage);
    if (m_iHealth <= 0)
        GameUI::getInstance()->incrementKilledEnemyNum();
}

void Gallo::sleep() {
    //isDead = true;
    m_bNeedRenderAttack = false;
    galloState = GALLO_INACTIVE;
    EnemySpawner::getInstance()->decrementLivingGallo();
    setVisible(false);
}