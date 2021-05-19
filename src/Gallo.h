#pragma once

#include "LivingEntity.h"

enum GalloState {
    GALLO_INACTIVE,
    GALLO_ONDEATH,
    GALLO_WANDER,
    GALLO_CHASE,
    GALLO_ATTACK
};

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
