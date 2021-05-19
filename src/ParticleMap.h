#pragma once

#include "Zy21586TileManager.h"
#include "Particle.h"


struct Particle;

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


    // tbc
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
