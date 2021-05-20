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

//the player is a subclass of LivingEntity which can be killed by enemies (named Gallo).
//the player has 3 sets of 3 - frame animations which are : idle, left, right.
//Note that the leftand right animations are not simply mirrored because of the same direction of shadowing.

//Visual Effect 
//1. When attacked by enemies (Gallo or DeadWall), the player sprite will flash with a lerped time interval to inform the player of the damage.
//2. When the HP is lower than 20%,  the player sprite will be masked with red color to inform the player.
class Player : public LivingEntity
{
protected:
    // singleton
    explicit Player(int iWidth = 64, int iHeight = 64, int iStartX = 220, int iStartY = 500, int iStartingHealth = 1000);
    static Player* pPlayer;

    PlayerState playerState{ PLAYER_IDLE };
    PlayerController* m_pPlayerController{ nullptr };//handles the user input with smoothened playing experience by check x/y collision separately to avoid some stark stops.
    Animator<PlayerState>* m_pAnimator{ nullptr };
    float m_fTakeHitEffectLerp{ 0.f };
    int m_iMoveSpeed{ 3 }; //4
    bool invincibleMode{ false };

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
    // invincible mode
    void switchInvincible() {
        invincibleMode = !invincibleMode;
    };
};

