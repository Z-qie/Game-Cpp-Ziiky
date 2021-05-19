
#pragma once

#include "BaseButton.h"
#include "Utils.h"

class ResetButton : public BaseButton
{
protected:
    // singleton
    explicit ResetButton(int iWidth = 150, int iHeight = 40, int iStartX = 350, int iStartY = 550);
    static ResetButton* pResetButton;

public:
    static ResetButton* getInstance();
    virtual ~ResetButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;
};

