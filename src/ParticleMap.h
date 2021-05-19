#pragma once

#include "Zy21586TileManager.h"
#include "Particle.h"

struct Particle;

//I designed a particle system to simulate a sand simulation by cellular automata algorithm on the Menu Scene and loading Scene.
//1. Inspired by famous game Noita: https://www.youtube.com/watch?v=prXuyMCgbTc
//2. By click left mouse button, the user can generate more particles into the scene; 
//by click right mouse button, the user can erase all the particles around the mouse position. 
//And all other particles will simulated the sand behavior to fill the erased gap.
//3. when the number of particles exceeds a specific number, the bottom level of particles will
//be eliminated to ensure there will not be too many of them!
//4. Each particle is a struct contains a fixed color to simulated a noise effect of sand.
class ParticleMap :
    public Zy21586TileManager
{
protected:
    // constructor
    ParticleMap(
        int iMapX, // width/col of map
        int iMapY, // height/row of map
        int iParticleSize); // size of partical

    static ParticleMap* m_pParticleMap;
public:
    static ParticleMap* getInstance();
    virtual ~ParticleMap() override;

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX,
        int iMapY,
        int iStartPositionScreenX,
        int iStartPositionScreenY) const override;

    void initParticleMap();
    void generateSpirit();
    void generateEmpty();
    void updateParticleMap();
    void updateSpirit(int iMapX, int iMapY);
    void setSpiritFollowMouse(bool b);
    void setEmptyFollowMouse(bool b);
    void setParticleAt(int iMapX, int iMapY, Particle pParticle);
    void setParticleAt(int iMapX, int iMapY, int id);
    // fetch the particle at x, y
    Particle& getParticleAt(int iMapX, int iMapY) const;
    int getParticleIdAt(int iMapX, int iMapY) const;

    virtual bool isEmpty(int x, int y) const override;

private:
    // array of all particles
    Particle* m_pParticles;
    bool m_bSpiritFollowMouse{ false };
    bool m_bEmptyFollowMouse{ false };
    int m_iSpiritNum{ 0 };
    int m_iLastUpdateTime{ 0 };
    float m_fDeltaSecond{ 0.f };

};
