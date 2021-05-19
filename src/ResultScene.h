
#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class ResultUI;
class DiscardButtion;
class ConfirmButton;

//After winning the game,  you are transferred to this scene to show your record and compare with the best record. 
//You will be asked to input your name with alphabetic character within  a length of 25. 
//Of course you can discard your record and go back to menu directly.
class ResultScene :public BaseScene
{
public:
    ResultScene() {};

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;
    virtual void virtMainLoopPreUpdate() override;
    virtual void virtPreDraw() override;
    virtual void virtPostDraw() override;

private:
    ResultUI* pResultUI{nullptr};
    DiscardButtion* m_pDiscardButton{ nullptr };
    ConfirmButton* m_pConfirmButton{ nullptr };
};
