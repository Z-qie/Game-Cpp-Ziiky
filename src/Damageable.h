#pragma once

class Damageable
{
public:
    Damageable() {};
    virtual ~Damageable() {};
    virtual void takeHit(int damage) = 0;
};
