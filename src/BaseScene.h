#pragma once

class Zy21586Engine;

//The basic structure of each scene to handle different event such as onCreation, onDestroy, onActivate, onDeactivate..
class BaseScene
{
public:
    BaseScene() {};
    virtual ~BaseScene() {};

    // called when scene initially created. called only once when Engine start.
    virtual void onCreate() = 0;

    // called when scene destroyed. called at most once (if a scene 
    // is not removed from the game, this will never be called - save maybe? 
    virtual void onDestroy() = 0;

    // called whenever a scene is transitioned into. 
    // called many times when in a pause-resume case
    virtual void onActivate() {};

    // called whenever a transition out of a scene occurs. 
    // can be called many times as OnActive.
    virtual void onDeactivate() {};

    // update
    virtual void virtMainLoopPreUpdate() {};
    virtual void virtMainLoopPostUpdate() {};

    // fixed update
    virtual void virtMainLoopDoBeforeUpdate() {};
    virtual void virtMainLoopDoAfterUpdate() {};

    // render
    virtual void virtPreDraw() {};
    virtual void virtDrawStringsUnderneath() {};
    virtual void virtDrawStringsOnTop() {};
    virtual void virtPostDraw() {};

    // handle input 
    virtual void virtMouseDown(int iButton, int iX, int iY) {};
    virtual void virtMouseUp(int iButton, int iX, int iY) {};
    virtual void virtKeyDown(int iKeyCode) {};
    virtual void virtMouseWheel(int x, int y, int which, int timestamp) {};


protected:
    Zy21586Engine* pEngine{ nullptr };

};
