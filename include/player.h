#pragma once

#include "raylib-cpp.hpp"
#include "input.h"
#include "room.h"

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

    void Update(const Input& input, const Room& room);
    void Draw();
};

Player::Player(rl::Vector2 position) : position(position)
{
}

Player::~Player()
{
}

void Player::Update(const Input &input, const Room& room)
{
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
    

    CollisionResult collisionResult = room.CheckMovementCollision(position.x, position.y, xToMove, yToMove, 32, 32);

    if (!collisionResult.collideX)
    {
        position.x += xToMove;
    }
    if (!collisionResult.collideY)
        position.y += yToMove;

    rl::Vector2 a = rl::Vector2(input.GetAxisHorizontal(), input.GetAxisVertical());
    float angle = a.Angle(rl::Vector2(1,0));
    // float angle = atan2f(a.y, a.x) + PI/2;

    
    // ::TraceLog(TraceLogLevel::LOG_INFO, std::to_string(angle).c_str());
}

void Player::Draw()
{
    ::DrawRectangle(position.GetX(), position.GetY(), 32, 32, GREEN);

    ::DrawText(std::to_string(direction).c_str(), 16, 16 + 32*4, 32, BLACK);
}