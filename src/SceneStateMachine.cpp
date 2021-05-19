#pragma once

#include "header.h"
#include "SceneStateMachine.h"

SceneStateMachine* SceneStateMachine::pSceneStateMachine = nullptr;
SceneStateMachine* SceneStateMachine::getInstance()
{
    if (pSceneStateMachine == nullptr) {
        pSceneStateMachine = new SceneStateMachine();
    }
    return pSceneStateMachine;
}

void SceneStateMachine::addScene(std::shared_ptr<BaseScene> scene, SceneID id)
{
    auto inserted = scenes.insert(std::make_pair(id, scene));
    inserted.first->second->onCreate();
}

void SceneStateMachine::remove(SceneID id)
{
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        // ff the scene we are removing is the current scene, 
        // need to set that to a null to prevent updating it again
        if (pCurrentScene == it->second)
            pCurrentScene = nullptr;

        // We make sure to call the OnDestroy method 
        // of the scene we are removing.
        std::cout << (int)it->first << std::endl;

        it->second->onDestroy();

        std::cout << (int)it->first << std::endl;
        scenes.erase(it);
    }
}

void SceneStateMachine::switchTo(SceneID id)
{
    auto it = scenes.find(id);

    if (it != scenes.end())
    {
        // If we have a current scene, we call its OnDeactivate method.
        if (pCurrentScene)
            pCurrentScene->onDeactivate();

        // Setting the current scene ensures that it is updated and drawn.
        pCurrentScene = it->second;
        m_CurrentSceneID = it->first;
        pCurrentScene->onActivate();
    }
}
// update
void SceneStateMachine::virtMainLoopPreUpdate() {
    if (pCurrentScene)
        pCurrentScene->virtMainLoopPreUpdate();
};

void SceneStateMachine::virtMainLoopPostUpdate() {
    if (pCurrentScene)
        pCurrentScene->virtMainLoopPostUpdate();
};

// fixed update
void SceneStateMachine::virtMainLoopDoBeforeUpdate() {
    if (pCurrentScene)
        pCurrentScene->virtMainLoopDoBeforeUpdate();
};

void SceneStateMachine::virtMainLoopDoAfterUpdate() {
    if (pCurrentScene)
        pCurrentScene->virtMainLoopDoAfterUpdate();
};

// render
void SceneStateMachine::virtPreDraw() {
    if (pCurrentScene) 
        pCurrentScene->virtPreDraw();
};

void SceneStateMachine::virtDrawStringsUnderneath() {
    if (pCurrentScene)
        pCurrentScene->virtDrawStringsUnderneath();
};

void SceneStateMachine::virtDrawStringsOnTop() {
    if (pCurrentScene)
        pCurrentScene->virtDrawStringsOnTop();
};

void SceneStateMachine::virtPostDraw() {
    if (pCurrentScene)
        pCurrentScene->virtPostDraw();
};

void SceneStateMachine::virtMouseDown(int iButton, int iX, int iY) {
    if (pCurrentScene)
        pCurrentScene->virtMouseDown(iButton, iX, iY);
}

void SceneStateMachine::virtMouseUp(int iButton, int iX, int iY) {
    if (pCurrentScene)
        pCurrentScene->virtMouseUp(iButton, iX, iY);
}

void SceneStateMachine::virtKeyDown(int iKeyCode) {
    if (pCurrentScene)
        pCurrentScene->virtKeyDown(iKeyCode);
}
