#pragma once

#include "Utils.h"
#include "Animator.h"
#include "GameObject.h"
#include "SceneStateMachine.h"

class SceneBG : public GameObject
{
protected:
    Animator<SceneID>* m_pAnimator{ nullptr };
     
public:
    SceneBG();
    ~SceneBG();
    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    void drawSprite() override;
};


