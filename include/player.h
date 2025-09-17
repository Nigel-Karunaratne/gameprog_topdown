#pragma once

#include "vendor/rlcpp/raylib-cpp.hpp"
#include "input.h"
#include "room.h"

#include <string>

namespace rl = raylib;

class Player
{
private:
    rl::Vector2 position;
    int direction = 0;
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
    int xToMove = input.GetAxisHorizontal();
    int yToMove = input.GetAxisVertical();

    //TODO - identify nearby tiles and check against them ONLY
    //TODO - separate horizontal and vertical checks
    bool collide = false;
    for(int y = 0; y < 10; ++y)
    {
        for(int x = 0; x < 10; ++x)
        {
            if (room.tiles[y][x].collide)
            {
                Rectangle wallTileRect = (Rectangle) {x*32,y*32,32,32};
                if (::CheckCollisionRecs((Rectangle){position.x + xToMove, position.y + yToMove, 32, 32}, wallTileRect) )
                {
                    collide = true;
                    break;
                }
            }
        }
    }

    if (!collide)
    {
        position.x += xToMove;
        position.y += yToMove;
    }

    rl::Vector2 a = rl::Vector2(input.GetAxisHorizontal(), input.GetAxisVertical());
    float angle = a.Angle(rl::Vector2(1,0));
    // float angle = atan2f(a.y, a.x) + PI/2;

    
    ::TraceLog(TraceLogLevel::LOG_INFO, std::to_string(angle).c_str());
}

void Player::Draw()
{
    ::DrawRectangle(position.GetX(), position.GetY(), 32, 32, GREEN);

    ::DrawText(std::to_string(direction).c_str(), 16, 16 + 32*4, 32, BLACK);
}