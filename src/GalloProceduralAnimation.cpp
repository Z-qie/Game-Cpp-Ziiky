#pragma once

#include "header.h"
#include "Gallo.h"
#include "Player.h"

#include "Zy21586Engine.h"

int Gallo::iGalloBodyRadius = 12;
int Gallo::iGalloShadowOffset = 2;
int Gallo::iInnerOffset = 1;
int Gallo::iAttackVisualOffset = 25;
int Gallo::iDarkGrey = 0x151515;
int Gallo::iDeathWithe = 0xffffff;
int Gallo::iWireEffectRadius = 6;
int Gallo::iWireEffectClampValue = iWireEffectRadius * 4;
int Gallo::iWireEffectDensity = 20;

void Gallo::virtDraw() {

    if (galloState == GALLO_ONDEATH) {
        m_fCurrentAttackEffectRadius = utils_lerp(m_fCurrentAttackEffectRadius, 35, 0.03f);
        int iCurrentAttackEffectRadius = static_cast<int>(m_fCurrentAttackEffectRadius);
        m_pEngine->getForegroundSurface()->drawHollowOval( // shadow
            m_iCurrentScreenX + iCurrentAttackEffectRadius - 15,
            m_iCurrentScreenY + iCurrentAttackEffectRadius - 15,
            m_iCurrentScreenX - iCurrentAttackEffectRadius + 15,
            m_iCurrentScreenY - iCurrentAttackEffectRadius + 15,

            m_iCurrentScreenX + iCurrentAttackEffectRadius - 15 - utils_rand(-3, 3),
            m_iCurrentScreenY + iCurrentAttackEffectRadius - 15 - utils_rand(-3, 3),
            m_iCurrentScreenX - iCurrentAttackEffectRadius + 15 + utils_rand(-3, 3),
            m_iCurrentScreenY - iCurrentAttackEffectRadius + 15 + utils_rand(-3, 3),
            iDeathWithe);

        m_pEngine->getForegroundSurface()->drawHollowOval( // shadow
            m_iCurrentScreenX + iCurrentAttackEffectRadius,
            m_iCurrentScreenY + iCurrentAttackEffectRadius,
            m_iCurrentScreenX - iCurrentAttackEffectRadius,
            m_iCurrentScreenY - iCurrentAttackEffectRadius,

            m_iCurrentScreenX + iCurrentAttackEffectRadius - utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenY + iCurrentAttackEffectRadius - utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenX - iCurrentAttackEffectRadius + utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenY - iCurrentAttackEffectRadius + utils_rand(-iWireEffectRadius, iWireEffectRadius),
            iDeathWithe);
    }
    else if (m_bNeedRenderAttack) {
        m_pEngine->drawForegroundOval( // shadow
            m_iCurrentScreenX + iGalloBodyRadius,
            m_iCurrentScreenY + iGalloBodyRadius,
            m_iCurrentScreenX - iGalloBodyRadius,
            m_iCurrentScreenY - iGalloBodyRadius,
            iDarkGrey);

        m_fCurrentAttackEffectRadius = utils_lerp(m_fCurrentAttackEffectRadius, 40, 0.03f);
        int iCurrentAttackEffectRadius = static_cast<int>(m_fCurrentAttackEffectRadius);

        m_pEngine->getForegroundSurface()->drawHollowOval( // shadow
            m_iCurrentScreenX + iGalloBodyRadius + iCurrentAttackEffectRadius,
            m_iCurrentScreenY + iGalloBodyRadius + iCurrentAttackEffectRadius,
            m_iCurrentScreenX - iGalloBodyRadius - iCurrentAttackEffectRadius,
            m_iCurrentScreenY - iGalloBodyRadius - iCurrentAttackEffectRadius,

            m_iCurrentScreenX + iGalloBodyRadius + iCurrentAttackEffectRadius - utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenY + iGalloBodyRadius + iCurrentAttackEffectRadius - utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenX - iGalloBodyRadius - iCurrentAttackEffectRadius + utils_rand(-iWireEffectRadius, iWireEffectRadius),
            m_iCurrentScreenY - iGalloBodyRadius - iCurrentAttackEffectRadius + utils_rand(-iWireEffectRadius, iWireEffectRadius),
            iDarkGrey);

        for (size_t i = 0; i < iWireEffectDensity; i++)
        {
            m_pEngine->drawForegroundTriangle(
                m_iCurrentScreenX, m_iCurrentScreenY,
                m_iCurrentScreenX + 2, m_iCurrentScreenY + 2,
                Player::getInstance()->getPosition().x + utils_rand(-iAttackVisualOffset, iAttackVisualOffset),
                Player::getInstance()->getPosition().y + utils_rand(-iAttackVisualOffset, iAttackVisualOffset),
                iDarkGrey); // dark grey
        }
    }

    else if (galloState == GALLO_WANDER || galloState == GALLO_CHASE) {
        m_fCurrentAttackEffectRadius = 0;
        m_pEngine->drawForegroundOval( // shadow
            m_iCurrentScreenX + iGalloBodyRadius,
            m_iCurrentScreenY + iGalloBodyRadius,
            m_iCurrentScreenX - iGalloBodyRadius,
            m_iCurrentScreenY - iGalloBodyRadius,
            iDarkGrey);
        m_pEngine->drawForegroundOval( // body
            m_iCurrentScreenX + iGalloBodyRadius - iGalloShadowOffset,
            m_iCurrentScreenY + iGalloBodyRadius - iGalloShadowOffset,
            m_iCurrentScreenX - iGalloBodyRadius,
            m_iCurrentScreenY - iGalloBodyRadius,
            0x333333);
        switch (galloDir)
        {
        case RIGHT:
            m_pEngine->drawForegroundOval( // eye
                m_iCurrentScreenX + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY + iGalloBodyRadius - 4 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenX + iGalloBodyRadius + 1 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY - iGalloBodyRadius + 4 + utils_rand(-iInnerOffset, iInnerOffset),
                0xaaaaaa);
            m_pEngine->drawForegroundOval( // eye ball
                m_iCurrentScreenX + 1 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY + 6 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenX + 13 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY - 6 + utils_rand(-iInnerOffset, iInnerOffset),
                galloState == GALLO_CHASE ? 0x200000 : 0x151515);
            break;

        case LEFT:
            //eye
            m_pEngine->drawForegroundOval( // eye
                m_iCurrentScreenX + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY + iGalloBodyRadius - 4 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenX - iGalloBodyRadius - 1 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY - iGalloBodyRadius + 4 + utils_rand(-iInnerOffset, iInnerOffset),
                0xaaaaaa);
            m_pEngine->drawForegroundOval( // eye ball
                m_iCurrentScreenX - 1 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY + 6 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenX - 13 + utils_rand(-iInnerOffset, iInnerOffset),
                m_iCurrentScreenY - 6 + utils_rand(-iInnerOffset, iInnerOffset),
                galloState == GALLO_CHASE ? 0x200000 : 0x151515);
            break;
        default:
            break;
        }

        // shadow!
        m_pEngine->drawForegroundOval(
            m_iCurrentScreenX + 5,
            m_iCurrentScreenY + 22 - 2,
            m_iCurrentScreenX - 5,
            m_iCurrentScreenY + 22 + 2,
            0x313131);

        //draw mesh
        for (size_t i = 0; i < iWireEffectDensity; i++)
        {
            m_pEngine->drawForegroundLine(
                utils_clamp(
                    utils_rand(m_iCurrentScreenX - iWireEffectClampValue, m_iCurrentScreenX + iWireEffectClampValue),
                    m_iCurrentScreenX - iWireEffectRadius, m_iCurrentScreenX + iWireEffectRadius),
                utils_clamp(
                    utils_rand(m_iCurrentScreenY - iWireEffectClampValue, m_iCurrentScreenY + iWireEffectClampValue),
                    m_iCurrentScreenY - iWireEffectRadius, m_iCurrentScreenY + iWireEffectRadius),
                utils_clamp(
                    utils_rand(m_iCurrentScreenX - iWireEffectClampValue, m_iCurrentScreenX + iWireEffectClampValue),
                    m_iCurrentScreenX - iWireEffectRadius, m_iCurrentScreenX + iWireEffectRadius),
                utils_clamp(
                    utils_rand(m_iCurrentScreenY - iWireEffectClampValue, m_iCurrentScreenY + iWireEffectClampValue),
                    m_iCurrentScreenY - iWireEffectRadius, m_iCurrentScreenY + iWireEffectRadius),
                0x313131);
        }
    }

    //drawSprite();

}