#pragma once

#include <list>
#include "GameObject.h"
#include "Utils.h"
#include "Animator.h"
#include "ThunderBolt.h"
#include "ThunderZoneController.h"
#include "Animator.h"

enum ThunderZoneState {
    THUNDER_IDLE, 
    THUNDER_ACTIVE,
    THUNDER_COOLDOWN
};


class ThunderZone : public GameObject
{
private:
    std::list<std::shared_ptr<ThunderBolt>> m_oThunderBoltList;
    std::unique_ptr<Animator<ThunderZoneState>> m_pAnimator{ nullptr };
    ThunderZoneController* m_pThunderZoneController;
    ThunderZoneState thunderZoneState{ THUNDER_IDLE };
    int m_iLastupdateTime{ 0 };

public:
    static float fThunderZoneMaxTime;
    static float fThunderZoneRemainTime;
    static float fThunderZoneRecoverSpeed;

    static int iThunderZoneDamage;
    static float fThunderZoneRadius;
    static float fThunderZoneRadiusMax;


    explicit ThunderZone(int iSize = 100);
    ~ThunderZone() {
        delete m_pThunderZoneController;
        //std::cout << "deleteing ThunderZone" << std::endl;
    };

    void virtStart() override;
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

    void castThunderBoltAt(const Vec2& target);
    void updateAllThunderBolts();
    void drawAllThunderBolts();
    void drawSprite() override;
};




