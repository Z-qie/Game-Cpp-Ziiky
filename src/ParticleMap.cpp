#pragma once

#include "header.h"
#include "Particle.h"
#include "ParticleMap.h"
#include "Zy21586Engine.h"
#include "Utils.h"
#include "SceneStateMachine.h"

ParticleMap* ParticleMap::m_pParticleMap = nullptr;

ParticleMap* ParticleMap::getInstance()
{
    if (m_pParticleMap == nullptr) {
        m_pParticleMap = new ParticleMap(base_window_width / 2, base_window_height / 2, 2);
    }
    return m_pParticleMap;
};

// constructor
ParticleMap::ParticleMap(
    int iMapX,
    int iMapY,
    int iParticleSize)
    :Zy21586TileManager(iMapX, iMapY, iParticleSize)
{
    setTopLeftPositionOnScreen(0, 0);
    initParticleMap();
}

// destructor
ParticleMap::~ParticleMap()
{
    m_pParticleMap = nullptr;
    if (m_pParticles != NULL)
        delete[] m_pParticles;
    m_pParticles = nullptr;
}

// initialize all particles as empty particle inside the map
void ParticleMap::initParticleMap() {
    m_pParticles = new Particle[m_iMapHeight * m_iMapWidth];
   
    if (SceneStateMachine::getInstance()->getCurrentSceneID() == SceneID::MENU) {
        // generate many spirits at the begining hahahahah
        for (int y = m_iMapHeight - 1; y >= 0; --y)
        {
            for (int x = m_iMapWidth - 1; x >= 0; --x)
            {
                if (utils_rand(0, 1000) < 40)
                    setParticleAt(
                        // use clamp to restrict the boundary inside the screen/tile map
                        utils_clamp_g(x, 0, getMapWidth() - 1),
                        utils_clamp_g(y, 0, getMapHeight() - 1),
                        particle_id_spirit);
            }
        }
    }

    if (SceneStateMachine::getInstance()->getCurrentSceneID() == SceneID::LOADING) {
        std::cout << "initParticleMap" << std::endl;
        for (int y = m_iMapHeight - 1; y >= 320; --y)
        {
            for (int x = m_iMapWidth - 1; x >= 0; --x)
            {
                if (utils_rand(0, 100) < 40)
                    setParticleAt(
                        // use clamp to restrict the boundary inside the screen/tile map
                        utils_clamp_g(x, 0, getMapWidth() - 1),
                        utils_clamp_g(y, 320, getMapHeight() - 1),
                        particle_id_spirit);
            }
        }
    }
}


void ParticleMap::virtDrawTileAt(
    BaseEngine* pEngine,
    DrawingSurface* pSurface,
    int iMapX,
    int iMapY,
    int iStartPositionScreenX,
    int iStartPositionScreenY) const {

    if (getParticleAt(iMapX, iMapY).m_id == particle_id_spirit) {
        pSurface->drawRectangle(
            iStartPositionScreenX,	// Left
            iStartPositionScreenY,	// Top
            iStartPositionScreenX + getTileWidth() - 1,		// Right
            iStartPositionScreenY + getTileHeight() - 1,	// Bottom
            getParticleAt(iMapX, iMapY).m_iColour
        );	// Pixel colour
    }
}

void ParticleMap::updateParticleMap() {

    generateSpirit();
    generateEmpty();

    m_iSpiritNum = 0;

    int iCurrentTime = Zy21586Engine::getInstance()->getModifiedTime();
    // loop thru bottom to top!
    for (int y = m_iMapHeight - 1; y >= 0; --y)
    {
        for (int x = m_iMapWidth - 1; x >= 0; --x)
        {
            int id = getParticleAt(x, y).m_id;

            m_fDeltaSecond = static_cast<float>(iCurrentTime - m_iLastUpdateTime) / 1000.f;

            switch (id) {
            case particle_id_spirit:
                updateSpirit(x, y);
                ++m_iSpiritNum;
                break;
            case particle_id_empty:
                break;
            }
        }
    }

    // erase spirit at bottom if too many haha
    if (m_iSpiritNum > m_iMapHeight * m_iMapWidth / 5) {
        for (int x = m_iMapWidth - 2; x >= 1; --x) {
            setParticleAt(
                x,
                getMapHeight() - 1,
                particle_id_empty);
        }

    }

    m_iLastUpdateTime = iCurrentTime;
}


void ParticleMap::generateEmpty() {
    if (m_bEmptyFollowMouse) {
        int mouseX = Zy21586Engine::getInstance()->getCurrentMouseX();
        int mouseY = Zy21586Engine::getInstance()->getCurrentMouseY();

        int eraseRadiusX = 5;
        int eraseRadiusY = 5;

        // set all particle in area around mouse as empty
        for (int x = -eraseRadiusX; x < eraseRadiusX; x++)
        {
            for (int y = -eraseRadiusY; y < eraseRadiusY; y++)
            {
                if (utils_rand(0, 100) < 60)
                    setParticleAt(
                        // use clamp to restrict the boundary inside the screen/tile map
                        utils_clamp_g(getMapXForScreenX(mouseX) + x, 0, getMapWidth() - 1),
                        utils_clamp_g(getMapYForScreenY(mouseY) + y, 0, getMapHeight() - 1),
                        particle_id_empty);
            }
        }
    }
}

void ParticleMap::generateSpirit() {
    if (m_bSpiritFollowMouse) {
        int mouseX = Zy21586Engine::getInstance()->getCurrentMouseX();
        int mouseY = Zy21586Engine::getInstance()->getCurrentMouseY();

        int generateRadiusX = 10;
        int generateRadiusY = 10;
        int generateStrength = 15;
        // set some particle in area around mouse as empty
        for (size_t i = 0; i < generateStrength; i++)
        {
            setParticleAt(
                utils_clamp_g(getMapXForScreenX(mouseX) + utils_rand(-generateRadiusX, generateRadiusX), 0, getMapWidth() - 1),
                utils_clamp_g(getMapYForScreenY(mouseY) + utils_rand(-generateRadiusY, generateRadiusY), 0, getMapHeight() - 1),
                particle_id_spirit);
        }
    }

    // random sand ========================================================
    for (size_t i = 30; i < 550; i++)
    {
        if (utils_rand(0, 6000) < 1)
            setParticleAt(
                utils_clamp_g(getMapXForScreenX(i) + utils_rand(-15, 15), 0, getMapWidth() - 1),
                utils_clamp_g(getMapYForScreenY(170) + utils_rand(-15, 15), 0, getMapHeight() - 1),
                particle_id_spirit);
    }

    // particles in Menu
    if (SceneStateMachine::getInstance()->getCurrentSceneID() == SceneID::MENU) {
        // at hat tip
        if (utils_rand(0, 1000) < 500)
            setParticleAt(
                utils_clamp_g(getMapXForScreenX(450) + utils_rand(-10, 10), 0, getMapWidth() - 1),
                utils_clamp_g(getMapYForScreenY(160) + utils_rand(-10, 10), 0, getMapHeight() - 1),
                particle_id_spirit);
        if (utils_rand(0, 1000) < 300)
            setParticleAt(
                utils_clamp_g(getMapXForScreenX(480) + utils_rand(-10, 10), 0, getMapWidth() - 1),
                utils_clamp_g(getMapYForScreenY(160) + utils_rand(-10, 10), 0, getMapHeight() - 1),
                particle_id_spirit);
    }
    // particles in loading
    if (SceneStateMachine::getInstance()->getCurrentSceneID() == SceneID::LOADING) {
        // at hat tip
        if (utils_rand(0, 100) < 80)
            setParticleAt(
                utils_clamp_g(getMapXForScreenX(360) + utils_rand(-100, 100), 0, getMapWidth() - 1),
                utils_clamp_g(getMapYForScreenY(360) + utils_rand(-10, 10), 0, getMapHeight() - 1),
                particle_id_spirit);
    }
}

void ParticleMap::setSpiritFollowMouse(bool b) {
    m_bSpiritFollowMouse = b;
}

void ParticleMap::setEmptyFollowMouse(bool b) {
    m_bEmptyFollowMouse = b;
}


void ParticleMap::updateSpirit(int iMapX, int iMapY)
{
    // fetch particle at Position iMapX iMapY
    Particle& particle = getParticleAt(iMapX, iMapY);
    int id = particle.m_id;
    float fGravity = 5.f;

    particle.m_fVelocityY = utils_clamp_g(particle.m_fVelocityY + (fGravity * m_fDeltaSecond), -20.f, 20.f);


    // check if can move directly beneath. If not, then reset velocity.
    if (isInBounds(iMapX, iMapY + 1) && !isEmpty(iMapX, iMapY + 1)) {
        particle.m_fVelocityY /= 2.f;
    }

    int nextX = iMapX + static_cast<int>(particle.m_fVelocityX);
    int nextY = iMapY + static_cast<int>(particle.m_fVelocityY);

    // Check to see if you can swap first with other element below you
    //int idBeneath = getParticleAt(iMapX, iMapY + 1).m_id;
    //int idBeneathRight = getParticleAt(iMapX + 1, iMapY + 1).m_id;
    //int idBeneathLeft = getParticleAt(iMapX - 1, iMapY + 1).m_id;

    Particle tmpA = particle;

    // falling with velocity
    if (isInBounds(nextX, nextY) && isEmpty(nextX, nextY)) {
        Particle tmpB = getParticleAt(nextX, nextY);
        setParticleAt(nextX, nextY, tmpA);
        setParticleAt(iMapX, iMapY, tmpB);
    }
    // Simple falling with halving the velocity Y
    else if (isInBounds(iMapX, iMapY + 1) && isEmpty(iMapX, iMapY + 1)) {

        particle.m_fVelocityY += fGravity * m_fDeltaSecond;

        Particle temp = getParticleAt(iMapX, iMapY + 1);
        setParticleAt(iMapX, iMapY + 1, tmpA);
        setParticleAt(iMapX, iMapY, temp);
    }
    else if (isInBounds(iMapX - 1, iMapY + 1) && isEmpty(iMapX - 1, iMapY + 1)) {
        particle.m_fVelocityX = utils_rand(0, 1) == 0 ? -1.f : 1.f;
        particle.m_fVelocityY += fGravity * m_fDeltaSecond;

        Particle temp = getParticleAt(iMapX - 1, iMapY + 1);
        setParticleAt(iMapX - 1, iMapY + 1, tmpA);
        setParticleAt(iMapX, iMapY, temp);

    }
    else if (isInBounds(iMapX + 1, iMapY + 1) && isEmpty(iMapX + 1, iMapY + 1)) {

        particle.m_fVelocityX = utils_rand(0, 1) == 0 ? -1.f : 1.f;
        particle.m_fVelocityY += fGravity * m_fDeltaSecond;

        Particle temp = getParticleAt(iMapX + 1, iMapY + 1);
        setParticleAt(iMapX + 1, iMapY + 1, tmpA);
        setParticleAt(iMapX, iMapY, temp);
    }
}

void ParticleMap::setParticleAt(int iMapX, int iMapY, Particle particle) {
    m_pParticles[iMapX + iMapY * m_iMapWidth] = particle;
}


void ParticleMap::setParticleAt(int iMapX, int iMapY, int id) {
    int index = iMapX + iMapY * m_iMapWidth;
    //m_pParticles[index].m_fLifeTime = 0;

    switch (id)
    {
    default:
    case particle_id_empty:
        m_pParticles[index].m_id = particle_id_empty;
        m_pParticles[index].m_iColour = 0x000000;
        break;
    case particle_id_spirit: {
        int colorNoiseStrength = utils_rand(0, 50);
        int colorNoise = ((1 << 24) + (colorNoiseStrength << 16) + (colorNoiseStrength << 8) + colorNoiseStrength);        // r g b respectively
        m_pParticles[index].m_id = particle_id_spirit;
        m_pParticles[index].m_iColour = 0xffffff - colorNoise; // set white with random greyish hue
        break;
    }

    }
}



Particle& ParticleMap::getParticleAt(int iMapX, int iMapY) const {
    return m_pParticles[iMapX + iMapY * m_iMapWidth];
}

int ParticleMap::getParticleIdAt(int iMapX, int iMapY) const {
    return m_pParticles[iMapX + iMapY * m_iMapWidth].m_id;
}

//int ParticleMap::getParticleColourAt(int iMapX, int iMapY) const {
//    return m_pParticles[iMapX + iMapY * m_iMapWidth].m_iColour;
//}
//
//int ParticleMap::incrementLifeTimeAt(int iMapX, int iMapY) {
//    //TBC with time
//    ++m_pParticles[iMapX + iMapY * m_iMapWidth].m_fLifeTime;
//}

bool ParticleMap::isEmpty(int x, int y) const {
    return isInBounds(x, y) && getParticleIdAt(x, y) == particle_id_empty;
}


