
#pragma once
//Used together with CollisionSystem, specifying a game object can collide actively to others.
class Collidable
{
public:
    virtual bool checkCollision() = 0;
};