#pragma once

#include <queue>
#include "GameObject.h"
#include "Animator.h"
#include <queue>
#include "Utils.h"

enum InstructionUIState {
    INTRO_NONE,
    INTRO_IDLE
};

class ViewCamera;


class InstructionUI : public GameObject
{
protected:
    InstructionUI();
    static InstructionUI* pInstructionUI;
    InstructionUIState instructionUIState{ INTRO_IDLE };
    Animator<InstructionUIState>* m_pAnimator{ nullptr };

public:
    //GameUI() {};

    static InstructionUI* getInstance();
    virtual ~InstructionUI() override {
        pInstructionUI = nullptr;
        delete m_pAnimator;
    };

    virtual void virtStart() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw()override;
    virtual void drawSprite()override;


    virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtMouseMoved(int iX, int iY) override;
    virtual void virtMouseUp(int iButton, int iX, int iY) override;
    //virtual void virtKeyDown(int iKeyCode)override;

    void drawZoomAlert();
    void drawReturnButton();
    void drawInstructionMsg();
    void resetBG();

private:
    bool m_bIsBeingDragged{ false };
    int m_iStartOfDragX, m_iStartOfDragY, m_iInitialClickedDragX, m_iInitialClickedDragY;

    ViewCamera* pCamera{ nullptr };
};

