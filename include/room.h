#pragma once

#include "raylib-cpp.hpp"
#include <vector>

typedef struct Tile {
    Color c;
    bool collide;
} Tile;

typedef struct CollisionResult {
    bool collideX;
    bool collideY;
} CollisionResult;

namespace rl = raylib;

class Room
{
private:
public:
    std::vector<std::vector<Tile>> tiles;
    int ySize = 9;
    int xSize = 10;

    Room();
    ~Room();

    CollisionResult CheckMovementCollision(int x, int y, int xToMove, int yToMove, int xSize=32, int ySize=32) const;

    void Draw();
};

Room::Room()
{
    ySize = 8;
    xSize = 10;
    for (int y = 0; y < ySize; ++y)
    {
        tiles.push_back(std::vector<Tile>());
        for (int x = 0; x < xSize; ++x)
        {
            bool val = (y == 0 || y == 7 /*|| x == 0 || x == 9*/);
            tiles[y].push_back((Tile){val ? RED : BLACK, val});
        }
    }
}

Room::~Room()
{
}

inline CollisionResult Room::CheckMovementCollision(int posX, int posY, int xToMove, int yToMove, int xSize, int ySize) const
{
    //TODO - identify nearby tiles and check against them ONLY (broad phase --> narrow phase)
    //TODO - separate up, down, left, right checks
    CollisionResult returnVal = (CollisionResult){false, false};
    for(int y = 0; y < this->ySize; ++y)
    {
        for(int x = 0; x < this->xSize; ++x)
        {
            if (this->tiles[y][x].collide)
            {
                //NOTE - at some point, change rectangle to use ints?
                Rectangle wallTileRect = (Rectangle) {x*32.0f,y*32.0f,32,32};
                if (::CheckCollisionRecs((Rectangle){(float)posX + xToMove, (float)posY, (float)xSize, (float)ySize}, wallTileRect) )
                {
                    returnVal.collideX = true;
                }
                else if (::CheckCollisionRecs((Rectangle){(float)posX, (float)posY + yToMove, (float)xSize, (float)ySize}, wallTileRect) )
                {
                    returnVal.collideY = true;
                }
            }
        }
    }
    
    return returnVal;
}

void Room::Draw()
{
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            if (tiles[y][x].collide)
            // ::DrawRectangleLines (x*32,y*32,32,32,tiles[y][x].c);
                ::DrawRectangle(x*32,y*32,32,32,tiles[y][x].c);
        }
    }
}