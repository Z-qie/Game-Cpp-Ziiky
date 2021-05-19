#pragma once

#include "header.h"
#include "PlayerController.h"
#include "Zy21586Engine.h"
#include "Player.h"
#include "CollisionSystem.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

PlayerState PlayerController::move() {
    PlayerState playerState;
    Vec2 moveInput{ 0,0 };
    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    Player* pPlayer = Player::getInstance();

    if (pEngine->isKeyPressed(SDLK_RIGHT) || pEngine->isKeyPressed(SDLK_d)) {
        playerState = PLAYER_RUN_RIGHT;
        moveInput.x = 1;
    }
    else if (pEngine->isKeyPressed(SDLK_LEFT) || pEngine->isKeyPressed(SDLK_a)) {
        playerState = PLAYER_RUN_LEFT;
        moveInput.x = -1;
    }
    else
    {
        playerState = PLAYER_IDLE;
    }
       
    if (pEngine->isKeyPressed(SDLK_DOWN) || pEngine->isKeyPressed(SDLK_s))
        moveInput.y = 1;
    else if (pEngine->isKeyPressed(SDLK_UP) || pEngine->isKeyPressed(SDLK_w))
        moveInput.y = -1;


    Vec2 moveVelocity = moveInput * pPlayer->getMoveSpeed();
    Vec2 target = moveVelocity + pPlayer->getPosition();

    // to enhance smooth experience
    if (CollisionSystem::checkObstacleBySquare(target.x, pPlayer->getPosition().y, m_iObstacleRadius))
        moveVelocity.x = 0;
    if (CollisionSystem::checkObstacleBySquare(pPlayer->getPosition().x, target.y, m_iObstacleRadius))
        moveVelocity.y = 0;

    pPlayer->translatePositionBy(moveVelocity);
    return playerState;
}

void PlayerController::lookAt() {
    Player* pPlayer = Player::getInstance();

    Zy21586Engine* pEngine = Zy21586Engine::getInstance();
    Vec2 mousePosition{ pEngine->getCurrentMouseX(), pEngine->getCurrentMouseY() };
    pPlayer->setAngle(utils_angle_btw_vecs(pPlayer->getPosition(), mousePosition));
}
