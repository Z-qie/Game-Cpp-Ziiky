#pragma once

#include "BaseButton.h"
#include "Utils.h"

class MenuQuitButton : public BaseButton
{
protected:
    // singleton
    explicit MenuQuitButton(int iWidth = 150, int iHeight = 40, int iStartX = 150, int iStartY = 600);
    static MenuQuitButton* pMenuQuitButton;

public:
    static MenuQuitButton* getInstance();
    virtual ~MenuQuitButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;

};

