#pragma once 

#include "header.h"
#include "GameUI.h"
#include "Player.h"
#include "GameCamera.h"
#include "ThunderZone.h"
#include "RuneManager.h"

GameUI* GameUI::pGameUI = nullptr;

GameUI::GameUI() {
    m_iTotalRuneNum = RuneManager::getInstance()->getTotalRuneNum();
    m_iTimeOffset = Zy21586Engine::getInstance()->getModifiedTime();
};

GameUI* GameUI::getInstance()
{
    if (pGameUI == nullptr) {
        pGameUI = new GameUI();
    }
    return pGameUI;
}


void GameUI::drawUI() {
    // bing with camera position
    GameCamera* pCamera = GameCamera::getInstance();
    setPosition(pCamera->getCameraPosition() + Vec2{ -base_window_width / 2 ,-base_window_height / 2 } + m_oLeftTopOffsetUI);

    drawLifeBar();
    drawThunderEnergyBar();
    drawActiveRuneNum();
    drawKilledEnemyNum();
    drawSurvivingTime();
    drawRenderFrame();
}

void GameUI::virtDoUpdate(int iCurrentTime) {
    Player* pPlayer = Player::getInstance();

    // set life percentage & life data string
    m_fCurrentLifePercent = static_cast<float>(pPlayer->getCurrentHealth()) / pPlayer->getStartingHealth();
    sprintf(m_LifeBarStr, "HP: %.0f%%", m_fCurrentLifePercent * 100);

    // set MP percentage & MP data string
    m_fCurrentEnergyPercent = ThunderZone::fThunderZoneRemainTime / ThunderZone::fThunderZoneMaxTime;
    sprintf(m_ThunderEnergyBarStr, "MP: %.0f%%", m_fCurrentEnergyPercent * 100);

    sprintf(m_EnemyKilledStr, "KILL:   %5d", m_iEnemyKilledNum);
    m_iActiveRuneNum = RuneManager::getInstance()->getCurrentRuneNum();
}

void GameUI::drawLifeBar() {
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1) - 1,
        getPosition().y + utils_rand(-1, 1),
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh + 1,
        getPosition().y + utils_rand(-1, 1),
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1) - 1,
        getPosition().y + utils_rand(-1, 1) + 15,
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh + 1,
        getPosition().y + utils_rand(-1, 1) + 15,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) - 1,
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) + 15 + 1,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) - 1,
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) + 15 + 1,
        0xe7fbff
    );

    // life bar inner bar
    m_pEngine->drawForegroundRectangle(
        getPosition().x + 4,
        getPosition().y + 4 + utils_rand(-1, 1),
        getPosition().x + utils_rand(-1, 1) + static_cast<int>(m_iLifeBarWitdh * m_fCurrentLifePercent) - 4,
        getPosition().y + 15 - 4 + utils_rand(-1, 1),
        0xffffff
    );

    // life bar data string
    m_pEngine->drawForegroundString(
        getPosition().x + m_iLifeBarWitdh + 7,
        getPosition().y - 3,
        m_LifeBarStr,
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 20)
    );
}

void GameUI::drawThunderEnergyBar() {
    // MP bg
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) + 25,
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) + 25,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) + 40,
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) + 40,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) + 25,
        getPosition().x + utils_rand(-1, 1),
        getPosition().y + utils_rand(-1, 1) + 40,
        0xe7fbff
    );
    m_pEngine->drawForegroundLine(
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) + 25,
        getPosition().x + utils_rand(-1, 1) + m_iLifeBarWitdh,
        getPosition().y + utils_rand(-1, 1) + 40,
        0xe7fbff
    );

    // MP inner bar
    int iCurrentTime = m_pEngine->getModifiedTime();
    if (m_iNextFlashTime < iCurrentTime) {    // if it's time to flash again, generate new flash form!!!
        m_iNextFlashTime = iCurrentTime + m_iBoltFlashDelay;

        Vec2 oStart = { getPosition().x + 2, getPosition().y + 25 + 10 };
        Vec2 oTarget = { getPosition().x + static_cast<int>(m_iThunderEnergyWitdh * m_fCurrentEnergyPercent), getPosition().y + 25 + 10 };

        m_iNumOfBreakPoint = (oTarget.x - oStart.x) / m_iBoltBreakPointDist;

        // formalize thunder 
        m_oThunderFlashLine.swap(std::queue<Vec2>()); // clear last flash form
        m_oThunderFlashLine.push(oStart);

        for (int i = 0; i < m_iNumOfBreakPoint - 1; i++)
            m_oThunderFlashLine.push(Vec2{
                getPosition().x + 4 + i * m_iBoltBreakPointDist + utils_rand(-2, 2),
                getPosition().y + 25 + 10 + utils_rand(-6, 6) });

        m_oThunderFlashLine.push(oTarget);

        // draw thunder
        Vec2 start = m_oThunderFlashLine.front();
        m_oThunderFlashLine.pop();

        while (!m_oThunderFlashLine.empty())
        {
            Vec2 next = m_oThunderFlashLine.front();
            m_pEngine->drawForegroundLine(
                start.x, start.y,
                next.x, next.y,
                0xbbedff);

            start = next;
            m_oThunderFlashLine.pop();
        }

        m_pEngine->drawForegroundOval(
            oTarget.x - 3,
            oTarget.y - 3,
            oTarget.x + 3,
            oTarget.y + 3,
            0xbbedff);
    }


    // thunder bar data string
    m_pEngine->drawForegroundString(
        getPosition().x + m_iThunderEnergyWitdh + 7,
        getPosition().y + 25 - 3,
        m_ThunderEnergyBarStr,
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 20)
    );
}

void GameUI::drawKilledEnemyNum() {
    m_pEngine->drawForegroundString(
        getPosition().x + base_window_width - 120,
        getPosition().y + 25,
        m_EnemyKilledStr,
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 20)
    );
}

void GameUI::drawSurvivingTime() {
    
    int seconds = (m_pEngine->getModifiedTime() - m_iTimeOffset) / 1000;
    m_iSurvivalTime = seconds;
    sprintf(m_SurvivingTimeStr, "Time:   %s", utils_getTimeStr(m_iSurvivalTime).c_str());

    m_pEngine->drawForegroundString(
        getPosition().x + base_window_width - 120,
        getPosition().y + 45,
        m_SurvivingTimeStr,
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 20)
    );
}

void GameUI::drawRenderFrame() {
    sprintf(m_FrameStr, "FRAME:   %4.0f", 1000 / static_cast<float>(m_pEngine->getModifiedTime() - iRenderLastTime));
    iRenderLastTime = m_pEngine->getModifiedTime();

    m_pEngine->drawForegroundString(
        getPosition().x + base_window_width - 120,
        getPosition().y + 65,
        m_FrameStr,
        0xffffff,
        m_pEngine->getFont("assets/fonts/AmaticBold.ttf", 20)
    );
}

void GameUI::drawActiveRuneNum() {
    for (int i = 0; i < m_iTotalRuneNum; i++)
    {
        m_pEngine->drawForegroundLine(
            getPosition().x + base_window_width - 55 - i * 20 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1),
            getPosition().x + base_window_width - 55 - i * 20 + 14 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1),
            0xe7fbff
        );

        m_pEngine->drawForegroundLine(
            getPosition().x + base_window_width - 55 - i * 20 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1) + 14,
            getPosition().x + base_window_width - 55 - i * 20 + 14 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1) + 14,
            0xe7fbff
        );
        m_pEngine->drawForegroundLine(
            getPosition().x + base_window_width - 55 - i * 20 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1),
            getPosition().x + base_window_width - 55 - i * 20 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1) + 14,
            0xe7fbff
        );
        m_pEngine->drawForegroundLine(
            getPosition().x + base_window_width - 55 - i * 20 + 14 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1),
            getPosition().x + base_window_width - 55 - i * 20 + 14 + utils_rand(0, 1),
            getPosition().y + utils_rand(-1, 1) + 14,
            0xe7fbff
        );

        if (m_iActiveRuneNum > 0)
            m_pEngine->drawForegroundRectangle(
                getPosition().x + base_window_width - 55 - i * 20 + utils_rand(-1, 1) + 1,
                getPosition().y + utils_rand(-1, 1) + 1,
                getPosition().x + base_window_width - 55 - i * 20 + 14 + utils_rand(-1, 1) - 1,
                getPosition().y + 14 + utils_rand(-1, 1) - 1,
                0xe6faff
            );
        --m_iActiveRuneNum;
    }
}