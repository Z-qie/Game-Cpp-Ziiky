#pragma once
#include "GameObject.h"
#include "Animator.h"
#include <queue>
#include "Utils.h"

enum WinUIState {
    WIN_NONE,
    WIN_LIGHTENGING
};


class WinUI : public GameObject
{
protected:
    WinUI();
    static WinUI* pWinUI;
    WinUIState winUIState{ WIN_LIGHTENGING };
    Animator<WinUIState>* m_pAnimator{ nullptr };

private:
    float m_fMergePercentage{ 0.0f };
    Vec2 m_iOffsetTitle{ 285, 640 };
 
public:

    static WinUI* getInstance();
    virtual ~WinUI() override {
        pWinUI = nullptr;  
        delete m_pAnimator;
    };
    // gameobject
    virtual void virtStart() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    void drawUI();
    //void drawLighteningEffect();
};

