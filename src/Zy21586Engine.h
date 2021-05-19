#pragma once

#include "BaseEngine.h"
#include "Utils.h"

constexpr auto fixed_update_in_millis = 1000 / 60; // 60fps
constexpr auto base_window_width = 720;
constexpr auto base_window_height = 720;

//class Player;
//class Gallo;
//class CaveGenerator;
//class EnemySpawner;
//class DeadWallSpawner;
class SceneStateMachine;
class RecordManager;


class Zy21586Engine : public BaseEngine
{
protected:
    Zy21586Engine();
    static Zy21586Engine* pMyEngine;

public:
    static Zy21586Engine* getInstance();

    ~Zy21586Engine()
    {
        pMyEngine = nullptr;

    };

    //virtual void virtSetupBackgroundBuffer() override;
    virtual int virtInitialiseObjects() override;
    // update
    virtual void virtMainLoopPreUpdate()override;
    virtual void virtMainLoopPostUpdate()override;

    // fixed update
    virtual void virtMainLoopDoBeforeUpdate()override;
    virtual void virtMainLoopDoAfterUpdate()override;

    // render
    virtual void virtPreDraw() override;
    virtual void virtDrawStringsUnderneath()override;
    virtual void virtDrawStringsOnTop()override;
    virtual void virtPostDraw()override;

    // handle input
    virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtMouseUp(int iButton, int iX, int iY) override;
    virtual void virtKeyDown(int iKeyCode) override;

    // handle resource release
    virtual void virtCleanUp() override;



    //	// State number - so we can support different states and demonstrate the basics.
    //	enum State { stateInit, stateMain, statePaused };
protected:
    //    CaveGenerator* pCaveGenerator{ nullptr };
    //    DeadWallSpawner* pDeadWallSpawner{ nullptr };
    //    EnemySpawner* pEnemySpawner{ nullptr };
    //    GameCamera* pCamera{ nullptr };
    //    Player* pPlayer{ nullptr };
    SceneStateMachine* pSceneStateMachine{ nullptr };
    RecordManager* pRecordManager{ nullptr };
};
