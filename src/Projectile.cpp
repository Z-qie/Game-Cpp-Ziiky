#pragma once

#include "header.h"
#include "Zy21586Engine.h"
#include "Projectile.h"
#include "LivingEntity.h"
#include "CollisionSystem.h"
#include "EnemySpawner.h"
#include "DeadWallSpawner.h"
#include "Gallo.h"
#include "GameCamera.h"

const int Projectile::iProjectileRadius = 20;
const int Projectile::iProjectileSpeed = 5;
const int Projectile::iProjectileVanishDelay = 1000;//ms
const int Projectile::iProjectileDamage = 1000;//500

const float Projectile::fBaseEffectRadiusFlyMax = 12.f; //12.f
const int Projectile::iEffectRadiusOffsetFly = 2;//2

const float Projectile::fBaseEffectRadiusHit = 30.f;//30.f


Projectile::Projectile(Vec2 from, Vec2 to)
    : m_oPosition(from)
    , m_oTarget(to)
    , m_oRawDirection(m_oTarget - m_oPosition) // this would enhance performance than use doubled value
{
}

bool Projectile::fly() {
    GameCamera* pCamera = GameCamera::getInstance();
    if (checkCollision() == true) { // if collide with new enemy/wall or colliding with enemy/wall
        return true;             // still consider it as flying
    }

    switch (projectileState)
    {
    case PROJECTILE_HIT: // if it was colliding with enemy, then if time to vanish
        return true;
    case PROJECTILE_NONE: // destory
        return false;
    case PROJECTILE_FLY: // no collision detected, make it fly!
        if (m_oPosition.x >= pCamera->getScreenX(base_window_width) ||
            m_oPosition.x <= pCamera->getScreenX(0) ||
            m_oPosition.y >= pCamera->getScreenY(base_window_height) ||
            m_oPosition.y <= pCamera->getScreenY(0))
        { // if out of boundary, delete it
            projectileState = PROJECTILE_NONE;
            return false;
        }
        else
        { //utils_debug(std::to_string(m_oRawDirection.x) +" " + std::to_string(m_oRawDirection.y));
            m_oPosition = m_oPosition + utils_offset_by_direction(static_cast<double>(iProjectileSpeed), m_oRawDirection);
            projectileState = PROJECTILE_FLY;
            return true;
        }
    default:
        return false;
        break;
    }
}

bool Projectile::checkCollision() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();

    if (projectileState == PROJECTILE_HIT) { // means hitting now!
        //std::cout << m_iVanishTime << std::endl;

        if (m_iVanishTime > pEngine->getModifiedTime()) {
            //iProjectileVanishDelay
            return true;  // still colliding with delay effect
        }
        else
        {
            projectileState = PROJECTILE_NONE;
            return false;
        }
    }
    else if (projectileState == PROJECTILE_FLY) {
        // check enemys
        //for (LivingEntity* enemy : pEngine->m_Enemys) {
        //for(Gallo* pGallo : EnemySpawner::getInstance()->p_Gallos)

        // to be generic!!!!!
        std::vector<Gallo*>gallos = EnemySpawner::getInstance()->getGallos();
        for (Gallo* pGallo : gallos) {
            if (CollisionSystem::checkCircles(
                m_oPosition.x,
                m_oPosition.y,
                pGallo->getPosition().x,
                pGallo->getPosition().y,
                iProjectileRadius)
                && !(pGallo->getGalloState() == GALLO_INACTIVE)) {
                projectileState = PROJECTILE_HIT;
                if (!(pGallo->getGalloState() == GalloState::GALLO_ONDEATH)) // remain effect but only take damge once
                    pGallo->takeHit(iProjectileDamage);
                m_iVanishTime = pEngine->getModifiedTime() + iProjectileVanishDelay;
                return true;
            }
        }

        //check walls
        DeadWallSpawner* pDealWalls = DeadWallSpawner::getInstance();
        if (pDealWalls->getMapValue(
            pDealWalls->getMapXForScreenX(m_oPosition.x),
            pDealWalls->getMapYForScreenY(m_oPosition.y)) == dead_wall_edge) {

            //this wall unit may take hit, but later....
            projectileState = PROJECTILE_HIT;
            m_iVanishTime = pEngine->getModifiedTime() + iProjectileVanishDelay;
            return true;
        }
    }
    return false;
}

int Projectile::getEffectRadiusFly() {
    int iSmoothness = 200;//200
    float lerpValue = 0.02f;//0.02

    // smoothly growth ever slower
    m_fCurrentBaseEffectRadiusFly = utils_lerp(m_fCurrentBaseEffectRadiusFly, fBaseEffectRadiusFlyMax, lerpValue);

    // ping-pong the radius based on time
    m_iCurentEffectRadius =
        static_cast<int>(m_fCurrentBaseEffectRadiusFly)
        + utils_ping_pong(Zy21586Engine::getInstance()->getModifiedTime() / iSmoothness, iEffectRadiusOffsetFly);

    return m_iCurentEffectRadius;
}

int Projectile::getEffectRadiusHit() {
    int iSmoothness = 1;

    // ping-pong the radius based on time
    m_iCurentEffectRadius =
        utils_ping_pong(Zy21586Engine::getInstance()->getModifiedTime() / iSmoothness, static_cast<int>(fBaseEffectRadiusHit));

    return m_iCurentEffectRadius;
}
