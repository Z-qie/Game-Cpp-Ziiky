#pragma once

#include "Utils.h"
#include "Collidable.h"

enum ProjectileState {
    PROJECTILE_NONE,
    PROJECTILE_FLY,
    PROJECTILE_HIT,
};

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
