#pragma once

#include "GameObject.h"

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

