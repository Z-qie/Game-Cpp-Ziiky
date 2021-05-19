#pragma once

class Player;
class Zy21586Engine;
enum PlayerState;

class PlayerController /*: public BaseController*/
{
private:
    int m_iObstacleRadius{ 18 };

public:
    PlayerController();
    ~PlayerController();

    //void handleInput() override;
    PlayerState  move();
    void lookAt();


    /* void LookAt(Vector3 lookPoint) {
        Vector3 heightCorrectedPoint = new Vector3(lookPoint.x, transform.position.y, lookPoint.z);
        transform.LookAt(heightCorrectedPoint);
    }*/
};
