#pragma once

#include "header.h"
#include "ThunderZoneController.h"
#include "Zy21586Engine.h"
#include "ThunderBolt.h"
#include "ThunderZone.h"
#include "Gallo.h"
#include "LivingEntity.h"
#include "CollisionSystem.h"
#include "EnemySpawner.h"
#include "Player.h"

ThunderZoneController::ThunderZoneController(ThunderZone* pThunderZone)
    : m_pThunderZone(pThunderZone)
{
}

ThunderZoneController ::~ThunderZoneController()
{
}

void ThunderZoneController::castSpell() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    // if is time to shoot?
    if (pEngine->getModifiedTime() > m_iNextCastTime) {
        m_iNextCastTime = pEngine->getModifiedTime() + m_iCastInterval;
        searchForEnemy();
    }
}

void ThunderZoneController::searchForEnemy() {
    Player* pPlayer = Player::getInstance();

    // to be generic!!!!!
    std::vector<Gallo*>gallos = EnemySpawner::getInstance()->getGallos();
    for (Gallo* pGallo : gallos) {
        if (CollisionSystem::checkCircles(
            pPlayer->getPosition().x,
            pPlayer->getPosition().y,
            pGallo->getPosition().x,
            pGallo->getPosition().y,
            static_cast<int>(ThunderZone::fThunderZoneRadius))
            && !(pGallo->getGalloState() == GalloState::GALLO_INACTIVE)
            && !pGallo->isTakingThunder()) { // if the enemy is active and not taking thunder, taking hit
            pGallo->setTakingThunder(true);
            if (!(pGallo->getGalloState() == GalloState::GALLO_ONDEATH)) // remain effect but only take damge once
                pGallo->takeHit(ThunderZone::iThunderZoneDamage); // damage enemy
            m_pThunderZone->castThunderBoltAt(pGallo->getPosition()); // cast bolt
            return;
        }
    }

    for (Gallo* pGallo : gallos)
        pGallo->setTakingThunder(false); // set back to make sure next thunder can hit on !!!!!!!!!!!!!!!!

}

