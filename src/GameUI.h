#pragma once

#include <queue>
#include "GameObject.h"

//This UI is a gameobjectl, with an inner debugPanel(can be helpful during dev. and debug), 
//to display the current state of the player, such as current HP, the number of Kills, 
//the number of Runes activated, surviving time and FPS.
//I intentionally designed and arranged an animated UI panel to present an active feeling for
//the player in the game with the colour scheme similar to the player (cyan and white).
class GameUI : public GameObject
{
protected:
    GameUI();
    static GameUI* pGameUI;

private:
    Vec2 m_oLeftTopOffsetUI{ 20,20 };

    // HP
    int m_iLifeBarWitdh{ 200 };
    float m_fCurrentLifePercent{ 1.f };
    char m_LifeBarStr[128]{ 0 };

    // MP
    int m_iThunderEnergyWitdh{ 200 };
    float m_fCurrentEnergyPercent{ 1.f };
    char m_ThunderEnergyBarStr[128]{ 0 };
    std::queue<Vec2> m_oThunderFlashLine;
    int m_iBoltFlashDelay{ 100 };
    int m_iNextFlashTime{ 0 };
    int m_iNumOfBreakPoint{ 0 };
    int m_iBoltBreakPointDist{ 10 };

    // killed
    int m_iEnemyKilledNum{ 0 };
    char m_EnemyKilledStr[128]{ 0 };

    // frame
    int iRenderLastTime{ 0 };
    char m_FrameStr[128]{ 0 };

    // surviving time
    int m_iSurvivalTime{ 0 };
    char m_SurvivingTimeStr[128]{ 0 };
    int m_iTimeOffset{ 0 };

    // rune activated
    //char m_ActivatRuneStr[128]{ 0 };
    int m_iTotalRuneNum{};
    int m_iActiveRuneNum{ 0 };

public:
    //GameUI() {};

    static GameUI* getInstance();
    virtual ~GameUI() override { pGameUI = nullptr; };

    virtual void virtDoUpdate(int iCurrentTime) override;
    void drawUI();
    void drawLifeBar();
    void drawThunderEnergyBar();
    void drawKilledEnemyNum();
    void drawSurvivingTime();
    void drawRenderFrame();
    void drawActiveRuneNum();

    void incrementKilledEnemyNum() { ++m_iEnemyKilledNum; };

    inline int getSurvivingTimeInSec() { return m_iSurvivalTime; };
    inline int getCurrentHP() { return  static_cast<int>(m_fCurrentLifePercent * 100); };
    inline int getNumOfKill() { return m_iEnemyKilledNum; };
};


