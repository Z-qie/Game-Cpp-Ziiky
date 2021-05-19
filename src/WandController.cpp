#pragma once

#include "header.h"
#include "WandController.h"
#include "Zy21586Engine.h"
#include "Projectile.h"
#include "Wand.h"

WandController::WandController(Wand* pWand)
    : m_pWand(pWand)
{
}

WandController ::~WandController()
{
}

void WandController::castSpell() {
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();

    if (m_pWand->getWandState() == WAND_MAGICSHOOT)
    {
        // if is time to shoot?
        if (pEngine->getModifiedTime() > m_iNextShootTime) {
            m_iNextShootTime = pEngine->getModifiedTime() + m_iCoolDownShoot;

            m_pWand->generateProjectileTo(Vec2{ pEngine->getCurrentMouseX(), pEngine->getCurrentMouseY() });
        }
    }
}



