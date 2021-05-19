#pragma once

#include <vector>
#include "header.h"
#include "Animation.h"
#include "SimpleImage.h"
#include "Zy21586Engine.h"

Animation::Animation(int interval)
    :m_iInterval(interval)
{
}

void Animation::addFrame(SimpleImage newFrame) {
    m_oFrames.push_back(newFrame);
}

bool Animation::updateFrame()
{
    if (m_oFrames.size() > 0)
    {
        if (m_iInterval != 0) { // animated based on set interval.
            int iCurrentTime = Zy21586Engine::getInstance()->getModifiedTime();

            if (m_iNextFrameTime < iCurrentTime)
            {
                incrementFrame();
                m_iNextFrameTime = iCurrentTime + m_iInterval;
                return true;
            }
        }
        else {// animated randomly
            if (utils_rand(1,100) < 50)
            {
                incrementFrame();
                return true;
            }
        }
    }
    return false;
}

void Animation::incrementFrame()
{
    //rollover
    m_iCurrentFrameIndex = (m_iCurrentFrameIndex + 1) % m_oFrames.size();
}

void Animation::reset()
{
    m_iCurrentFrameIndex = 0;
    m_iNextFrameTime = 0;
}


const SimpleImage& Animation::getCurrentFrame() const
{
    return m_oFrames[m_iCurrentFrameIndex];
}