#pragma once

#include "Utils.h"
#include "Collidable.h"

enum ProjectileState {
    PROJECTILE_NONE,
    PROJECTILE_FLY,
    PROJECTILE_HIT,
};

//1. Projectile is not a game object but rather a Collidable class contains information of the projectile position, 
//when to explore, if hit enemies or walls. 
//2. It is the wand's job to render animation of each projectile based on their states.<
//3. Flying: when initialized with mouse direction, the projectile starts at the exact position of wand's orb and flies to that direction at speed 5. 
//While flying, the bolt grows at the speed tuned by **smooth-step algorithm by lerp** until it hit some enemies, walls, 
//or disappear if out of the camera's view.
//4. Explode: when hit enemies or walls, it causes damages(1000 on gallo) and plays an explosion procedural animation by implementing a ping-ping algorithm 
//to bounce the size of the projectile while a blue cast shadow for delayed seconds (1s).
class Projectile : public Collidable
{
public:
    static const int iProjectileRadius;
    static const int iProjectileSpeed;
    static const int iProjectileVanishDelay;
    static const int iProjectileDamage;

    static const float fBaseEffectRadiusFlyMax;
    static const int iEffectRadiusOffsetFly;

    static const float fBaseEffectRadiusHit;
    //static const int iBaseEffectRadiusFly;

private:
    int m_iVanishTime{ 0 };
    int m_iCurentEffectRadius{ 0 };
    float m_fCurrentBaseEffectRadiusFly{ 0.f };

public:
    ProjectileState projectileState{ PROJECTILE_FLY };
    Vec2 m_oPosition{ 0,0 };
    Vec2 m_oTarget{ 0,0 };
    Vec2 m_oRawDirection{ 0,0 };// this would enhance performance than use doubled value
    Projectile(Vec2 from, Vec2 to);
    ~Projectile() {};

    bool fly();
    bool checkCollision() override;
    Vec2 getPosition() const { return m_oPosition; };
    int getEffectRadiusFly();
    int getEffectRadiusHit();
};
