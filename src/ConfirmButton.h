#pragma once

#include "BaseButton.h"
#include "Utils.h"

class ConfirmButton : public BaseButton
{
protected:
    // singleton
    explicit ConfirmButton(int iWidth = 150, int iHeight = 40, int iStartX = 480, int iStartY = 620);
    static ConfirmButton* pConfirmButton;

public:
    static ConfirmButton* getInstance();
    virtual ~ConfirmButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;
};

