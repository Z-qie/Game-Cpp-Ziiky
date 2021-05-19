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

//This is a menu scene with a interactable sand simulation system.
//By click left mouse button, the user can generate more particles into the scene;
//by click right mouse button, the user can erase all the particles around the mouse position.
//And all other particles will simulated the sand behavior to fill the erased gap.
//when the number of particles exceeds a specific number, the bottom level of particles will be 
//eliminated to ensure there will not be too many of them
//Each particle is a struct contains a fixed color to simulated a noise effect of sand.
//Of course it is still a menu page  with four animated button.
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
