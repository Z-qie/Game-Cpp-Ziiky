#pragma once
#include "BaseScene.h"
#include "SceneStateMachine.h"

class ParticleMap;
//class MenuButtonMap;
class SceneBG;
class MenuStartButton;
class MenuIntroButton;
class MenuRecordButton;
class MenuQuitButton;


class MenuScene :public BaseScene
{
public:
    MenuScene() {};

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;
    virtual void virtMainLoopPreUpdate() override;
    virtual void virtPreDraw() override;
    virtual void virtPostDraw() override;

    virtual void virtMouseDown(int iButton, int iX, int iY);
    virtual void virtMouseUp(int iButton, int iX, int iY) ;

    // check if to switch scene
    //void setSwitchToScene(SceneID id);

private:
    //SceneID m_SceneSwitchedID{ SceneID::MENU };
    ParticleMap* m_pParticleMap{ nullptr };
    SceneBG* m_pSceneBG{ nullptr };

    // UI buttons
    MenuStartButton* m_pMenuStartButton{ nullptr };
    MenuIntroButton* m_pMenuIntroButton{ nullptr };
    MenuRecordButton* m_pMenuRecordButton{ nullptr };
    MenuQuitButton* m_pMenuQuitButton{ nullptr };
};
