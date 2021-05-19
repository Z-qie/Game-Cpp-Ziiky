#pragma once

#include <vector>
#include "SimpleImage.h"

//Each animation has several images/sprites as a set of frames and controls the fps of the animation.
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
