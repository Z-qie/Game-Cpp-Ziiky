
#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class ResultUI;
class DiscardButtion;
class ConfirmButton;

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


    // input 
    // check if to switch scene
    //void setSwitchToScene(SceneID id);

private:
    ResultUI* pResultUI{nullptr};
    DiscardButtion* m_pDiscardButton{ nullptr };
    ConfirmButton* m_pConfirmButton{ nullptr };
};
