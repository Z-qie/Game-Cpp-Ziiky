#pragma once
#include "GameObject.h"
#include "Animator.h"
#include <queue>
#include "Utils.h"

enum WinUIState {
    WIN_NONE,
    WIN_LIGHTENGING
};

//Similar to GameOverUI, when the player has activated all the runes (though it is not trivial to achieve that lol,
//I secretly added a developer sugar to let you win directly during the debug/test by pressing "o", don't tell any others please,between you and me.)
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

