
#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class RecordUI;
class ResetButton;

//In this scene you can view the best record made by previous players. And you are allow to reset the record with a rest button.
class RecordScene :public BaseScene
{
public:
    RecordScene() {};

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;
    virtual void virtMainLoopPreUpdate() override;
    virtual void virtPreDraw() override;
    virtual void virtPostDraw() override;
    virtual void virtKeyDown(int iKeyCode)override;

private:
    RecordUI* pRecordUI{ nullptr };
    ResetButton* pResetButton{ nullptr };
};
