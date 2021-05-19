#pragma once

#include "Utils.h"

class DeadWallUnit
{
public:
    Vec2 m_oAttackPosition{ 0,0 };
    bool isLeftEmpty{ false };
    bool isRightEmpty{ false };
    bool isTopEmpty{ false };
    bool isBottomEmpty{ false };
    bool foundPlayer{ false };
    int m_iColor{ 0x151515 };
    int m_iEffectRadius = 2;


    static bool canChangeIdlePosition;
    static bool canChangeAttackPosition;
    static int iAttackDetectionRadius;
    static int iIdleVisualRadius;
    static int iAttackVisualOffset;
    static int iDamage;
    static bool isPlayerTakingHit;


    const Vec2& getAttackPosition(int startX, int startY);
};

