#pragma once

#include <vector>
#include "SimpleImage.h"

class Animation
{
protected:
    int m_iInterval{ 500 };
    int m_iCurrentFrameIndex{ 0 };
    int m_iNextFrameTime{ 0 };
    std::vector<SimpleImage> m_oFrames;

public:
    Animation(int interval);
    ~Animation() {};
    void addFrame(SimpleImage newFrame);
    bool updateFrame();
    void incrementFrame();
    void reset();
    const SimpleImage& getCurrentFrame() const;

};
