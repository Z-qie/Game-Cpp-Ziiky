#pragma once

#include <list>
#include "GameObject.h"
#include "Projectile.h"
#include "Utils.h"
#include "Animator.h"
#include "WandController.h"

enum WandState {
    WAND_NONE,
    WAND_IDLE,
    WAND_MAGICSHOOT
};

class Zy21586Engine;

class Wand : public GameObject
{
private:
    std::list<std::shared_ptr<Projectile>> m_oProjectileList;
    WandController* m_pWandController;
    Vec2 m_oOffsetToPlayer{ 0, -35 };
    WandState wandState{ WAND_IDLE };
    std::unique_ptr<Animator<WandState>> m_pAnimator{ nullptr };

public:
    explicit Wand(int iSize = 10);
    ~Wand() {
       delete m_pWandController;
       std::cout << "deleteing Wand" << std::endl;
    };

    void virtStart() override;
    void virtDraw() override;
    void virtDoUpdate(int iCurrentTime) override;
    long virtNotify(int iSignalNumber, int x, int y) override; // auto shot
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtMouseUp(int iButton, int iX, int iY) override;

    WandState getWandState() { return wandState; };
    void generateProjectileTo(const Vec2& target);
    void updateAllProjectiles();
    void drawAllProjectiles();
    void drawSprite() override;
};


