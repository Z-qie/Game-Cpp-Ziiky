#pragma once

#include "BaseButton.h"
#include "Utils.h"

class MenuStartButton : public BaseButton
{
protected:
    // singleton
    explicit MenuStartButton(int iWidth = 150, int iHeight = 40, int iStartX = 150, int iStartY = 450);
    static MenuStartButton* pMenuStartButton;

public:
    static MenuStartButton* getInstance();
    virtual ~MenuStartButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;

};

