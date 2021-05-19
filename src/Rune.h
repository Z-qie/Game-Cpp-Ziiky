#pragma once

#include "GameObject.h"
#include "Animator.h"
#include "ThunderBolt.h"

enum RuneState {
    RUNE_NONE,
    RUNE_IDLE,
    RUNE_ACTIVATING,
    RUNE_ACTIVE
};


class Rune : public GameObject
{
private:
    RuneState runeState{ RUNE_IDLE };
    Animator<RuneState>* m_pAnimator{ nullptr };
    static const int iDetectRadius;
    static const float fThunderZoneRadius;
    static const int iDamage;

    int m_iActivatingTime{ 1500 };
    int m_iActivingRemainTime{ 1500 };
    int m_iActiveRemainTime{ 5000 };
    int m_iStartActiveTime{ 0 };

    std::list<std::shared_ptr<ThunderBolt>> m_oThunderBoltList;



public:
    Rune(int x, int y);
    virtual ~Rune();
    // gameobject
    virtual void virtStart() override;
    virtual void virtDraw() override;
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void drawSprite() override;

    void castThunderBoltAt(const Vec2& target);
    void updateAllThunderBolts();
    void drawAllThunderBolts();
    void castSpell();

    RuneState getState() { return runeState; };
};

