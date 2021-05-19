#pragma once

#include "BaseButton.h"
#include "Utils.h"

class DiscardButtion : public BaseButton
{
protected:
    // singleton
    explicit DiscardButtion(int iWidth = 150, int iHeight = 40, int iStartX = 250, int iStartY = 620);
    static DiscardButtion* pDiscardButtion;

public:
    static DiscardButtion* getInstance();
    virtual ~DiscardButtion() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;

};

