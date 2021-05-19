
#pragma once
#include <type_traits>
#include <memory>
#include "BaseScene.h"
#include "SceneStateMachine.h"
#include "GameCamera.h"
#include "Zy21586Engine.h"

class Player;
class Gallo;
class GameUI;
class PauseUI;
class WinUI;
class GameOverUI;
class RuneManager;
class CaveGenerator;
class GroundRenderer;
class EnemySpawner;
class DeadWallSpawner;

//Where the player plays the game.Controls all the elements in the game : Map generator, enemy spawner, camera, environment render, UIs...
//Has three inner state as * *Pause, Game overand Win** .
class GameScene :public BaseScene
{
    //Wand* m_pWand{nullptr};
public:

    virtual void onCreate() override;
    virtual void onDestroy() override;
    virtual void onActivate() override;
    virtual void onDeactivate() override;

    // update
    virtual void virtMainLoopPreUpdate();
    virtual void virtMainLoopPostUpdate();

    // fixed update
    virtual void virtMainLoopDoBeforeUpdate();
    virtual void virtMainLoopDoAfterUpdate();

    // render
    virtual void virtPreDraw();
    virtual void virtDrawStringsUnderneath();
    virtual void virtDrawStringsOnTop();
    virtual void virtPostDraw();

    // input 
    virtual void virtKeyDown(int iKeyCode);

    //void setSwitchToScene(SceneID id);
    void enableDebug(); // to be UI 

    //int getScreenX(int x) { return x - pCamera->getOffset().x; };
    //int getScreenY(int y) { return y - pCamera->getOffset().y; };
    //void lose() { m_bLose = true; };
    //void win() { m_bWin = true; };

private:
    RuneManager* pRuneManager{ nullptr };
    CaveGenerator* pCaveGenerator{ nullptr };
    GroundRenderer* pGroundRenderer{ nullptr };
    DeadWallSpawner* pDeadWallSpawner{ nullptr };
    EnemySpawner* pEnemySpawner{ nullptr };
    GameCamera* pCamera{ nullptr };
    Player* pPlayer{ nullptr };
    GameUI* pGameUI{ nullptr };
    PauseUI* pPauseUI{ nullptr };
    GameOverUI* pGameOverUI{ nullptr };
    WinUI* pWinUI{ nullptr };
    //bool m_bBackToMenu{ false };
    bool m_bLose{ false };
    bool m_bWin{ false };

};
