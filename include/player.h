#pragma once

#include "raylib-cpp.hpp"
#include "input.h"
#include "world.h"

#include <string>

namespace rl = raylib;

class Player
{
private:
    rl::Vector2 position;
    int direction = 0;

    bool item1 = false;
    bool item2 = false;

public:
    Player(rl::Vector2 position);
    ~Player();

    void Update(const Input& input, World& world);
    void Draw();
};

Player::Player(rl::Vector2 position) : position(position)
{
}

Player::~Player()
{
}

void Player::Update(const Input &input, World& world)
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

    // After movement, check if on bounds of screen. If so, ask World to trigger room swap.
    world.CheckIfSideRoomExists(-1,0);
    if (position.x <= 0) //Left
    {
        if (world.CheckIfSideRoomExists(-1,0))
        {
            world.ChangeActiveRoom(-1,0);
            position.x = 288;
        }
        else
            position.x = 0;
    }
    else if (position.x >= 288) // Right
    {
        if (world.CheckIfSideRoomExists(1,0))
        {
            world.ChangeActiveRoom(1,0);
            position.x = 0;
        }
        else
            position.x = 288;
    }
    else if (position.y <= 0) // Top
    {
        if (world.CheckIfSideRoomExists(0,-1))
        {
            world.ChangeActiveRoom(0,-1);
            position.y = 224;
        }
        else
            position.y = 0;
    }
    else if (position.y >= 224) // Bottom
    {
        if (world.CheckIfSideRoomExists(0,1))
        {
            world.ChangeActiveRoom(0,1);
            position.y = 0;
        }
        else
            position.y = 224;
    }


    float angle = a.Angle(rl::Vector2(1,0));
    // float angle = atan2f(a.y, a.x) + PI/2;

    
    // ::TraceLog(TraceLogLevel::LOG_INFO, std::to_string(angle).c_str());
}

void Player::Draw()
{
    ::DrawRectangle(position.GetX(), position.GetY(), 32, 32, GREEN);

    ::DrawText(std::to_string(direction).c_str(), 16, 16 + 32*4, 32, BLACK);
}