#pragma once

#include "BaseButton.h"
#include "Utils.h"

class MenuIntroButton : public BaseButton
{
protected:
    // singleton
    explicit MenuIntroButton(int iWidth = 150, int iHeight = 40, int iStartX = 150, int iStartY = 500);
    static MenuIntroButton* pMenuIntroButton;

public:
    static MenuIntroButton* getInstance();
    virtual ~MenuIntroButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;
};

