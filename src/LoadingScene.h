#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class ParticleMap;
class LoadingUI;

class LoadingScene :public BaseScene
{
public:
    LoadingScene() {};

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;

    virtual void virtMainLoopPreUpdate() override;
    virtual void virtPreDraw() override;

    virtual void virtKeyDown(int iKeyCode);
    //virtual void virtMouseDown(int iButton, int iX, int iY);
    //virtual void virtMouseUp(int iButton, int iX, int iY);
    // 
    // check if to switch scene
    void checkForTime();
    void setSwitchToScene(SceneID id);

private:
    int m_iDisplayInterval{ 8000 };
    int m_CurrentSTime{ 0 };
    SceneID m_SceneSwitchedID{ SceneID::GAME };
    LoadingUI* m_pLoadingUI{ nullptr };
    ParticleMap* m_pParticleMap{ nullptr };

};
