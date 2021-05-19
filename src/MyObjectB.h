#pragma once
#include "DisplayableObject.h"

class MyObjectB :
    public DisplayableObject
{
public:
    MyObjectB(BaseEngine*);
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
};

