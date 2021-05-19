#pragma once

#include "Utils.h"
#include "Animator.h"
#include "LivingEntity.h"

enum PlayerState {
    PLAYER_NONE,
    PLAYER_IDLE,
    PLAYER_RUN_LEFT,
    PLAYER_RUN_RIGHT
};

class PlayerController;
class Wand;

class Player : public LivingEntity/*, public Collidable*/
{

protected:
    // singleton
    explicit Player(int iWidth = 64, int iHeight = 64, int iStartX = 220, int iStartY = 500, int iStartingHealth = 1000);
    static Player* pPlayer;

    PlayerState playerState{ PLAYER_IDLE };
    PlayerController* m_pPlayerController{ nullptr };
    Animator<PlayerState>* m_pAnimator{ nullptr };
    float m_fTakeHitEffectLerp{ 0.f };
    int m_iMoveSpeed{ 3 }; //4


    //Wand* m_pWand{nullptr};
public:
    static Player* getInstance();
    virtual ~Player() override;

    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
   
    // livingEntity
    virtual void takeHit(int damage) override;
    virtual void onDeath() override;

    //bool onCollisionEnter() override;
    int  getMoveSpeed() { return m_iMoveSpeed; };
    virtual void drawSprite() override;
};

