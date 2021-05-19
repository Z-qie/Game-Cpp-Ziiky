#pragma once

#include "header.h"
#include "ThunderBolt.h"
#include "Player.h"
#include "Utils.h"

const int ThunderBolt::iBoltFlashDelay = 150;
const int ThunderBolt::iBoltFlashTime = 1000;
const int ThunderBolt::iRandomOffsetThresholdX = 10;
const int ThunderBolt::iRandomOffsetThresholdY = 5;

// for thunder zone
ThunderBolt::ThunderBolt(Vec2 target)
    : m_oTarget(target)
    // set start position at the top of the camera
    , m_oStart(target.x, Player::getInstance()->getPosition().y - base_window_height / 2)
    , m_iFlashEndTime(Zy21586Engine::getInstance()->getModifiedTime() + iBoltFlashTime)
{
    m_iNumOfBreakPoint = (m_oTarget.y - m_oStart.y) / m_iBoltBreakPointDistY;
    //std::cout << "num of break point: " << m_iNumOfBreakPoint << std::endl;
}


// for rune
ThunderBolt::ThunderBolt(Vec2 target, Vec2 start)
    : m_oTarget(target)
    // set start position at the top of the camera
    , m_oStart(start)
    , m_iFlashEndTime(Zy21586Engine::getInstance()->getModifiedTime() + iBoltFlashTime)
{
    m_iNumOfBreakPoint = static_cast<int>(sqrt(utils_dist_square(m_oStart, m_oTarget)) / m_iBoltBreakPointDistY);
    //m_iNumOfBreakPoint = (abs(m_oTarget.y - m_oStart.y) + abs(m_oTarget.x - m_oStart.x)) / m_iBoltBreakPointDistY;
    m_iBoltBreakPointDistX = m_iNumOfBreakPoint == 0 ? 0 : (m_oTarget.x - m_oStart.x) / m_iNumOfBreakPoint;
    m_iBoltBreakPointDistY = m_iNumOfBreakPoint == 0 ? 0 : (m_oTarget.y - m_oStart.y) / m_iNumOfBreakPoint;
}

bool ThunderBolt::formalizeFlash() {
    int iCurrentTime = Zy21586Engine::getInstance()->getModifiedTime();

    // if time's out, destroy this thunder bolt
    if (m_iFlashEndTime < iCurrentTime)
        return false;

    // if it's time to flash again, generate new flash form!!!
    if (m_iNextFlashTime < iCurrentTime) {
        m_iNextFlashTime = iCurrentTime + iBoltFlashDelay;
        //thunderBoltState = ThunderBoltState::THUNDERBOLT_FLASHING;
        m_oThunderFlashLine.swap(std::queue<Vec2>()); // clear last flash form
        m_oThunderFlashLine.push(m_oStart);


        for (int i = 0; i < m_iNumOfBreakPoint - 1; i++)
        {
            m_oThunderFlashLine.push(Vec2{
                m_oStart.x + i * m_iBoltBreakPointDistX + utils_rand(-iRandomOffsetThresholdX, iRandomOffsetThresholdX),
                m_oStart.y + i * m_iBoltBreakPointDistY + utils_rand(-iRandomOffsetThresholdY, iRandomOffsetThresholdY) });
        }

        m_oThunderFlashLine.push(m_oTarget);
    }
    /*   else
       {
           thunderBoltState == ThunderBoltState::THUNDERBOLT_INTERVAL;
       }*/

    return true;
}