#pragma once

#include "header.h"
#include "Utils.h"
#include "Player.h"
#include "DeadWallUnit.h"

bool DeadWallUnit::canChangeIdlePosition = false;
bool DeadWallUnit::canChangeAttackPosition = false;
int DeadWallUnit::iAttackDetectionRadius = 90;
int DeadWallUnit::iIdleVisualRadius = 50;
int DeadWallUnit::iAttackVisualOffset = 40;
int DeadWallUnit::iDamage = 3;
bool DeadWallUnit::isPlayerTakingHit = false;

const Vec2& DeadWallUnit::getAttackPosition(int startX, int startY) {
    if (canChangeIdlePosition && !foundPlayer) { // get idle random position
        utils_rand(0, 0);
        m_oAttackPosition = {
            startX + utils_rand(isLeftEmpty ? -iIdleVisualRadius : -20, isRightEmpty ? iIdleVisualRadius : 20),
            startY + utils_rand(isTopEmpty ? -iIdleVisualRadius : -20, isBottomEmpty ? iIdleVisualRadius : 20),
        };
        m_iColor = 0x151515;

    }
    else if (canChangeAttackPosition && foundPlayer) { 
        if (!isPlayerTakingHit) {
            isPlayerTakingHit = true;
            Player::getInstance()->takeHit(iDamage);
        }
        m_iColor = 0x151515;
        Vec2 visualOffset = {
            utils_rand(-iAttackVisualOffset, iAttackVisualOffset),
            utils_rand(-iAttackVisualOffset, iAttackVisualOffset)
        };
        m_oAttackPosition = Player::getInstance()->getPosition() + visualOffset;
    }

    return m_oAttackPosition;
}