
#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class RecordUI;
class ResetButton;

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
