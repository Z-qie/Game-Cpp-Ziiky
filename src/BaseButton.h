#pragma once
#include "GameObject.h"
#include "Zy21586Engine.h"
#include "Animator.h"

enum ButtonState {
    NONE,
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_CLICK
};

//Specifying a game object that is an animated (see Animator&Animation class) button which can handle user mouse click/hover events.
class BaseButton : public GameObject
{
protected:
    bool m_bIsMouseHover{ false };
    ButtonState buttonState{ ButtonState::BUTTON_IDLE };
    Animator<ButtonState>* m_pAnimator{ nullptr }; // acc not all buttons need animator

public:
    BaseButton(int iWidth, int iHeight, int iStartX, int iStartY)
        :GameObject(iWidth, iHeight, iStartX, iStartY)
    {};

    virtual ~BaseButton() { delete m_pAnimator; };

    bool isClicked() { return buttonState == ButtonState::BUTTON_CLICK; };
    virtual void onClick() = 0;

    virtual void virtMouseMoved(int iX, int iY) override {
        //std::cout << iX << ">= " << m_iStartDrawPosX << ", " << iX <<"<= "<<m_iDrawWidth + m_iStartDrawPosX - 1<< std::endl;
        if (iX >= m_iCurrentScreenX - m_iDrawWidth/2 &&
            iX <= m_iCurrentScreenX + m_iDrawWidth / 2 &&
            iY >= m_iCurrentScreenY - m_iDrawHeight / 2 &&
            iY <= m_iCurrentScreenY + m_iDrawHeight / 2) {
            buttonState = ButtonState::BUTTON_HOVER;
        }
        else {
            buttonState = ButtonState::BUTTON_IDLE;
        }
    }

    virtual void virtMouseDown(int iButton, int iX, int iY) override {
        if (buttonState == ButtonState::BUTTON_HOVER && iButton == SDL_BUTTON_LEFT) {
            //buttonState = ButtonState::BUTTON_CLICK;
            onClick();
        }
    }
};

