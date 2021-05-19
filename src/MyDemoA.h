#pragma once
#include "BaseEngine.h"
#include "MyTileManager.h"


class MyDemoA :
    public BaseEngine
{
public:
    virtual void virtSetupBackgroundBuffer() override;
    virtual void virtMouseDown(int iButton, int iX, int iY) override;
    virtual void virtKeyDown(int iKeyCode) override;
    virtual int virtInitialiseObjects() override;


protected:
    MyTileManager m_TileManager;
};

