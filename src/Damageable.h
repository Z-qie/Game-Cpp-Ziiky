#pragma once
//Specifying a game object that can be damaged by attacks/spells by takeHit(int damage).
class Damageable
{
public:
    Damageable() {};
    virtual ~Damageable() {};
    virtual void takeHit(int damage) = 0;
};
