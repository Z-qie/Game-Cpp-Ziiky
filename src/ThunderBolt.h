#pragma once

#include <queue>
#include "Utils.h"

enum ThunderBoltState {
    THUNDERBOLT_NONE,
    THUNDERBOLT_INTERVAL,
    THUNDERBOLT_FLASHING,
};

class ThunderBolt
{
public:
    static const int iBoltFlashDelay;
    static const int iBoltFlashTime;
    static const int iRandomOffsetThresholdX;
    static const int iRandomOffsetThresholdY;


private:

    Vec2 m_oStart{ 0,0 };
    Vec2 m_oTarget{ 0,0 };
    int m_iNextFlashTime{ 0 };
    int m_iFlashEndTime{ 0 };
    int m_iNumOfBreakPoint{ 0 };

    int m_iBoltBreakPointDistX{ 0 };
    int m_iBoltBreakPointDistY{ 15 };

public:
    std::queue<Vec2> m_oThunderFlashLine;
    ThunderBoltState thunderBoltState{ ThunderBoltState::THUNDERBOLT_FLASHING };

    ThunderBolt(Vec2 target);
    ThunderBolt(Vec2 target, Vec2 Start);
    ~ThunderBolt() {};

    bool formalizeFlash();
    const Vec2& getTarget() { return m_oTarget; };

};

