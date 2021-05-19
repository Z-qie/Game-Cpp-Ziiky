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

//Instruction scene presents you a great (I reckon at least) hand-drawn user manual to teach you how to play the game. 
//It is scrollable and draggable by ViewCamera and two FilterPoints, have fun with it.
class InstructionUI : public GameObject
{
protected:
    InstructionUI();
    static InstructionUI* pInstructionUI;
    InstructionUIState instructionUIState{ INTRO_IDLE };
    Animator<InstructionUIState>* m_pAnimator{ nullptr };

public:
    static InstructionUI* getInstance();
    virtual ~InstructionUI() override {
        pInstructionUI = nullptr;
        delete m_pAnimator;
    };
    // update and render
    virtual void virtStart() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw()override;
    virtual void drawSprite()override;
    // input
    virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtMouseMoved(int iX, int iY) override;
    virtual void virtMouseUp(int iButton, int iX, int iY) override;
    // UI
    void drawZoomAlert();
    void drawReturnButton();
    void drawInstructionMsg();
    void resetBG();

private:
    bool m_bIsBeingDragged{ false };
    int m_iStartOfDragX, m_iStartOfDragY, m_iInitialClickedDragX, m_iInitialClickedDragY;

    ViewCamera* pCamera{ nullptr };
};

