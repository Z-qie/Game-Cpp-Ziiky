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

//All the runes are initialized in inactive state by RuneManager during map generation phase and controlled during the game. 
//When the player approaches a rune and activates it, the rune will go into activating state and release powerful spell to kill 
//all enemies around(400 radius) and finally go into active state delayed by 5 seconds. 
//After that this rune will no longer be needed and will be removed from the DisplayableObjectContainer and deleted.
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
    //cast spell
    void castThunderBoltAt(const Vec2& target);
    void updateAllThunderBolts();
    void drawAllThunderBolts();
    void castSpell();

    RuneState getState() { return runeState; };
};

