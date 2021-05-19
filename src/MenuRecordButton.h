
#pragma once

#include "BaseButton.h"
#include "Utils.h"

class MenuRecordButton : public BaseButton
{
protected:
    // singleton
    explicit MenuRecordButton(int iWidth = 150, int iHeight = 40, int iStartX = 150, int iStartY = 550);
    static MenuRecordButton* pMenuRecordButton;

public:
    static MenuRecordButton* getInstance();
    virtual ~MenuRecordButton() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void onClick() override;
    virtual void drawSprite() override;

};

