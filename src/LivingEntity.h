#pragma once
#include "Damageable.h"
#include "GameObject.h"

class LivingEntity : public GameObject, public Damageable
{
protected:
    int m_iStartingHealth{ 1000 };
    int m_iHealth{ 1000 };
    bool m_bIsDead{ false };

public:
    LivingEntity(int iWidth, int iHeight, int iStartX, int iStartY, int m_iStartingHealth = 1000)
        :GameObject(iWidth, iHeight, iStartX, iStartY)
    {};

    virtual ~LivingEntity() {};

    virtual void takeHit(int damage) override {
        if(!m_bIsDead)
            m_iHealth -= damage;

        if (m_iHealth <= 0 && !m_bIsDead) {
            die();
        }
    }

    bool isDead() { return m_bIsDead; };
    int getCurrentHealth() { return m_iHealth; };
    int getStartingHealth() { return m_iStartingHealth; };


protected:
    virtual void onDeath() = 0;

private:
    void die() {
        m_bIsDead = true;
        /* if (OnDeath != null) {
             OnDeath();
         }*/
        onDeath();
         // destory itself??
    }
};
