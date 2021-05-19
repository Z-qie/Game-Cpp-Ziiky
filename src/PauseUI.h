#pragma once

#include "GameObject.h"

class PauseUI : public GameObject
{
protected:
    PauseUI();
    static PauseUI* pPauseUI;

private:
    int m_iOffsetXBG{ 0 };
    Vec2 m_iOffsetTitle{ 280, 300 };

public:

    static PauseUI* getInstance();
    virtual ~PauseUI() override { pPauseUI = nullptr; };

    virtual void virtDoUpdate(int iCurrentTime) override;
    void drawUI();
  
};

