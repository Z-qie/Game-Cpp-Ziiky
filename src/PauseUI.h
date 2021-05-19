#pragma once

#include "GameObject.h"

//Similar to the GameOverUI, when pressing Space button, the game is paused (only the enemy movement, 
//player control and timer in the UI are paused, all other animation are remained) and a semi-transparent
//smoke effect is displayed on the game scene. Then, the player can choose to resume the game or go back to the Start Menu. 
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

