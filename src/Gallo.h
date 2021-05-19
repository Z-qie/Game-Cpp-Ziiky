#pragma once

#include "LivingEntity.h"

enum GalloState {
    GALLO_INACTIVE,
    GALLO_ONDEATH,
    GALLO_WANDER,
    GALLO_CHASE,
    GALLO_ATTACK
};

//1. We have two types of enemies. Gallo, the first one,  is a subclass of LivingEntity which can be killed by the player.
//2. States: gallo has 5 states and 4 behaviors :
//        1. Inactive : all dead / asleep gallos are inactive which are invisible and to be re - spawned by EnemySpawner 
//           at a position out of the view(see EenemySpawner below).
//        2. Wander : when gallos are far enough but not too far(300 - 1000 radius) from the player, they just keep wandering 
//           in a random speedand to a random position(100 radius from current position in an updating frequency as 5s max
//           (i.e if achieved earlier, then update directly to another random position, if not achieved in 5s, update forcefully to change position) 
//           while keep detecting the player.By doing this in 100 radius offset, if a player kills all the enemies aroundand stand still at the same 
//           position, the possibility that an enemy just being spawned can detect the player will be lower than if the player keeps moving.
//        3. Chase: when detecting the player, the gallo starts to chase the player with speed a little faster than player.
//           The target position is updated in a pre - set frequency(1s).
//        4. Attack : when the gallo is close enough(50 radius) to the player, it starts to attack the player in a frequency of 0.3s 
//           with damage 30 per attack(see animation below).
//        5. Sleep : when the gallo is even farther(1000 radius) from the player and consider the player will not be approached in the recent future, 
//           it stops wanderingand makes itself sleepand waits for the EnemySpawner to awake it at a new position again near the player.
//        6. OnDeath : when killed by the player, the gallo starts to play the death effect before finally disappearing. (see animation below)

class Gallo : public LivingEntity
{
private:
    GalloState galloState{ GALLO_INACTIVE };
    Direction galloDir{ LEFT };
    Vec2 m_oWanderCenter{ 0,0 };
    Vec2 m_oNextWanderPosition{ 0,0 };
    int m_iAttackEndTime{ 0 };
    int m_iDeadthEndTime{ 0 };
    int m_iNextValidTime{ 0 };
    float m_fCurrentAttackEffectRadius{ 0.f };

    bool m_bNeedRenderAttack{ false };
    bool m_bIstakingThunder{false};

    static int iPrecisionError;
    static int iInitGalloHealth;
    static int iMoveSpeed;
    static int iObstacleRadius;
    static int iWanderRadius;
    static int iWanderClampValue;
    static int iWanderFrequency;

    static int iDetectRadius;
    static int iSleepRadius;

    static int iChaseFrequency;
    static int iAttackRadius;
    static int iAttackInterval;
    static int iDamage;

    static int iWireEffectRadius;
    static int iWireEffectClampValue;
    static int iWireEffectDensity;
    static int iDeathEffectInterval;

    static int iGalloBodyRadius;
    static int iGalloShadowOffset;
    static int iInnerOffset;
    static int iAttackVisualOffset;
    static int iDarkGrey;
    static int iDeathWithe;
public:
    explicit Gallo(int iStartX = 40, int iStartY = 40, int iWidth = 60, int iHeight = 60, int iStartingHealth = 1000);
    ~Gallo() override {
        std::cout << "deleteing Gallo" << std::endl;
    };

    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual long virtNotify(int iSignalNumber, int x, int y) override { return 0; }; // maybe the treasure??
    virtual void onDeath() override;
    virtual void drawSprite();

    GalloState getGalloState() { return galloState; };
    void wakeUp(Vec2 initialPosition);
    void wander();
    void chase();
    void sleep(); // this means this gallo is not killed by player

    void attack();
    virtual void takeHit(int damage) override;
    bool isTakingThunder() { return m_bIstakingThunder; };
    void setTakingThunder(bool b) { m_bIstakingThunder = b; };
    //
};
