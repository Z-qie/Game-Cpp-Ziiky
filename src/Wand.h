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

//1. There is a wand flying around the player which can cast Magic Bolt (projectile class in code)(trigger by mouse and support auto shooting when pressed)
//2. The wand is a game object whose position controlled by the user's mouse position. 
//The wand will always be around the player (35 radius) and facing the direction to the mouse cursor.
//3. It is the wand's job to cast spell and produce projectiles to hit enemies.
//4. The wand has a 2-frame animation with images.
//5. To enhance a smoothened experience, I used states to control if the wands can produce magic bolts to allow the user keep firing 
//when keeping the left mouse down instead of the need of clicking multiple times.
//6. There is no limit on cast magic bolts, fire as you wish!
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


