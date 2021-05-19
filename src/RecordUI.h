

#pragma once

#include <queue>
#include "GameObject.h"

class RecordUI : public GameObject
{
protected:
    RecordUI();
    static RecordUI* pRecordUI;

public:
    static RecordUI* getInstance();
    virtual ~RecordUI() override { pRecordUI = nullptr; };

    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw()override;
    void drawReturnButton();
    void drawBackground();
    void drawBoardFrame();
    void drawRecord();

};

