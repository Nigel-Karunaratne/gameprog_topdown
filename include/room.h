#pragma once

#include "raylib-cpp.hpp"
#include <vector>

#include "texturemanager.h"

typedef struct Tile {
    int index;
    bool collide;
} Tile;

typedef struct CollisionResult {
    bool collideX;
    bool collideY;
} CollisionResult;

namespace rl = raylib;

#include <iostream>

class Room
{
private:
public:
    std::vector<std::vector<Tile>> tiles;
    int ySize = 8;
    int xSize = 10;

    Room();
    ~Room();

    CollisionResult CheckMovementCollision(int x, int y, int xToMove, int yToMove, int xSize=32, int ySize=32) const;

    void insertTileAt(int index, Tile tile);

    void Draw(const TextureManager& textureManager);

    void debug_print()
    {
        for (int y = 0; y < ySize; ++y)
        {
            for (int x = 0; x < xSize; ++x)
            {
                std::cout << tiles[y][x].index << ",";
            }
            std::cout << std::endl;
        }
    }
};

Room::Room()
{
    // ySize = 8;
    // xSize = 10;
    for (int y = 0; y < ySize; ++y)
    {
        tiles.push_back(std::vector<Tile>());
        for (int x = 0; x < xSize; ++x)
        {
            // bool val = (y == 0 || y == 7 /*|| x == 0 || x == 9*/);
            tiles[y].push_back((Tile){ 0, false });
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

inline void Room::insertTileAt(int index, Tile tile)
{
    int x = index % xSize;
    int y = (int) index / xSize;
    tiles[y][x] = tile;
}

void Room::Draw(const TextureManager& textureManager)
{
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            textureManager.DrawLevelTile(tiles[y][x].index, x*32, y*32, 32, 32);
        }

    }
}