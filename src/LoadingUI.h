

#pragma once

#include <queue>
#include "GameObject.h"
#include "Animator.h"

enum LoadingUIState {
    LOAD_NONE,
    LOAD_IDLE
};

// I intended to design a "fake" Loading Scene because we are doing mono-threading, 
// the loading cannot really load under the scene. But hopefully, this scene would smooth the cringgy feeling of 
// stark loading time and giving players a good feeling
class LoadingUI : public GameObject
{
protected:
    LoadingUI();
    static LoadingUI* pLoadingUI;
    LoadingUIState loadingUIStateState{ LOAD_IDLE };
    Animator<LoadingUIState>* m_pAnimator{ nullptr };

private:
    std::string userInput{ std::string() };
    int m_iStartTime{ 0 };
    int m_iCurrentTime{0};

public:

    static LoadingUI* getInstance();
    virtual ~LoadingUI() override {
        pLoadingUI = nullptr;
        delete m_pAnimator;
    };

    virtual void virtStart() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw()override;
};

