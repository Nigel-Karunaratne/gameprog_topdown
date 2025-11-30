#pragma once

#include "raylib-cpp.hpp"
#include "input.h"
#include "world.h"

#include "texturemanager.h"

#include <string>

#include <iostream>

namespace rl = raylib;

class Player
{
private:
    rl::Vector2 position;
    int direction = 0;
    bool is_moving = false;
    int movement_frame = 0;
    float _movement_frame_timer = 0.15;

    bool item1 = false;
    bool item2 = false;

public:
    Player(rl::Vector2 position);
    ~Player();

    void Update(float delta, const Input& input, World& world);
    void Draw(const TextureManager& textureManager);
};

Player::Player(rl::Vector2 position) : position(position)
{
}

Player::~Player()
{
}

void Player::Update(float delta, const Input &input, World& world)
{
    // if (isTransitioning)
        // return;
    // Process Input
    int xToMove = input.GetAxisHorizontal();
    int yToMove = input.GetAxisVertical();

    if (input.GetItem1Pressed() && item1)
    {
        // TODO - use item 1
    }
    else if (input.GetItem2Pressed() && item2)
    {
        // TODO - use item 2
    }
    

    CollisionResult collisionResult = world.CheckMovementCollision(position.x, position.y, xToMove, yToMove, 32, 32);

    if (!collisionResult.collideX)
    {
        position.x += xToMove;
    }
    if (!collisionResult.collideY)
        position.y += yToMove;

    rl::Vector2 a = rl::Vector2(input.GetAxisHorizontal(), input.GetAxisVertical());

    std::cout << this->direction << std::endl;
    if (a.LengthSqr() > 0.5)
    {
        this->direction = a.Angle((Vector2) { 0, -1 }) * (2/PI) + 2;
        this->is_moving = true;

        this->_movement_frame_timer -= delta;
        if (this->_movement_frame_timer <= 0)
        {
            this->_movement_frame_timer = 0.15;
            this->movement_frame = (this->movement_frame+1) % 2;
        }
    }
    else
        this->is_moving = false;

    // After movement, check if on bounds of screen. If so, ask World to trigger room swap.
    world.CheckIfSideRoomExists(-1,0);
    if (position.x <= 0) //Left
    {
        if (world.CheckIfSideRoomExists(-1,0))
        {
            world.ChangeActiveRoom(-1,0);
            position.x = 288 - 3;
        }
        else
            position.x = 0;
    }
    else if (position.x >= 288) // Right
    {
        if (world.CheckIfSideRoomExists(1,0))
        {
            world.ChangeActiveRoom(1,0);
            position.x = 0 + 3;
        }
        else
            position.x = 288;
    }
    else if (position.y <= 0) // Top
    {
        if (world.CheckIfSideRoomExists(0,-1))
        {
            world.ChangeActiveRoom(0,-1);
            position.y = 224 - 3;
        }
        else
            position.y = 0;
    }
    else if (position.y >= 224) // Bottom
    {
        if (world.CheckIfSideRoomExists(0,1))
        {
            world.ChangeActiveRoom(0,1);
            position.y = 0 + 3;
        }
        else
            position.y = 224;
    }
}

void Player::Draw(const TextureManager& textureManager)
{
    // ::DrawRectangle(position.GetX(), position.GetY(), 32, 32, GREEN);
    if (this->is_moving)
        textureManager.DrawPlayerMoving(this->direction, this->movement_frame, this->position.GetX(), this->position.GetY());
    else
        textureManager.DrawPlayerIdle(this->direction, this->position.GetX(), this->position.GetY());
}