
#pragma once

#include <queue>
#include "GameObject.h"

class ResultUI : public GameObject
{
protected:
    ResultUI();
    static ResultUI* pResultUI;

private:
    std::string userInput{ std::string() };


public:
    //GameUI() {};

    static ResultUI* getInstance();
    virtual ~ResultUI() override { pResultUI = nullptr; };

    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw()override;
    virtual void virtKeyDown(int iKeyCode)override;
    void drawBackground();
    void drawBoardFrame();
    void drawResult();

    std::string getPlayerName();

};

