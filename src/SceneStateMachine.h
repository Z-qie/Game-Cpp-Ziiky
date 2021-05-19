#pragma once

#include <memory>
#include <type_traits>
#include <unordered_map>
#include "BaseScene.h"

enum class SceneID
{
    NONE,
    MENU,
    LOADING,
    GAME,// gaming, pause, win(intermediate)
    RESULT, // win
    INSTRUCTION,
    RECORD

};

class SceneStateMachine
{

protected:
    SceneStateMachine() {};
    static SceneStateMachine* pSceneStateMachine;

public:
    static SceneStateMachine* getInstance();

    // update
    void virtMainLoopPreUpdate();
    void virtMainLoopPostUpdate();

    // fixed update
    void virtMainLoopDoBeforeUpdate();
    void virtMainLoopDoAfterUpdate();

    // render
    void virtPreDraw();
    void virtDrawStringsUnderneath();
    void virtDrawStringsOnTop();
    void virtPostDraw();

    // Adds a scene to the state machine and bind the id of that scene.
    void addScene(std::shared_ptr<BaseScene> scene, SceneID id);
    void switchTo(SceneID id);    // Transitions to scene with specified id.
    void remove(SceneID id);    // Removes scene from state machine.

     // handle input 
    void virtMouseDown(int iButton, int iX, int iY);
    void virtMouseUp(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);

    SceneID getCurrentSceneID() { return m_CurrentSceneID; };

private:
    std::unordered_map<SceneID, std::shared_ptr<BaseScene>> scenes;
    std::shared_ptr<BaseScene> pCurrentScene;
    SceneID m_CurrentSceneID{ SceneID::MENU };
};

