

#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class ViewCamera;
class InstructionUI;

class IntroScene :public BaseScene
{
public:
    IntroScene() {};

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;
    virtual void virtMainLoopPreUpdate() override;
    virtual void virtMainLoopDoBeforeUpdate() override;

    virtual void virtPreDraw() override;
    virtual void virtPostDraw() override;

 /*   virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtMouseUp(int iButton, int iX, int iY) override;*/
    virtual void virtKeyDown(int iKeyCode)override;


    // input 
    // check if to switch scene
    //void setSwitchToScene(SceneID id);

private:
    ViewCamera* pViewCamera{ nullptr };
    InstructionUI* pInstructionUI{nullptr};
};
