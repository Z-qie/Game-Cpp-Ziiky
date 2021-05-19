#pragma once

#include "GameObject.h"

//When the player is killed, the game Scene will display a Game Over UI with a drew picture(see screenshots below)
//as background to let the player to choose play again or back to the Start Menu. This UI is designed as an inner
//state of the GameScene instead of a separate scene because I intended to make the UI semi-transparent and still render
//the game scene (such as enemies and players) with only stop some specific elements (such as enemies's wandering, player controls and some data)
class GameOverUI : public GameObject
{
protected:
    GameOverUI();
    static GameOverUI* pGameOverUI;

private:
    float m_fMergePercentage{ 0.0f };
    Vec2 m_iOffsetTitle{ 230, 450 };

public:

    static GameOverUI* getInstance();
    virtual ~GameOverUI() override { pGameOverUI = nullptr; };

    virtual void virtDoUpdate(int iCurrentTime) override;
    void drawUI();
};

