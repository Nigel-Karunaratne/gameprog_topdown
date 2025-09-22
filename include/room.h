#pragma once

#include "vendor/rlcpp/raylib-cpp.hpp"
#include <vector>

typedef struct Tile {
    Color c;
    bool collide;
} Tile;

class Room
{
private:
public:
    std::vector<std::vector<Tile>> tiles;
    int xSize;
    int ySize;

    Room();
    ~Room();

    void Draw();
};

Room::Room()
{
    ySize = 9;
    xSize = 10;
    for (int y = 0; y < ySize; ++y)
    {
        tiles.push_back(std::vector<Tile>());
        for (int x = 0; x < xSize; ++x)
        {
            bool val = (y == 0 || y == 8 || x == 0 || x == 9);
            tiles[y].push_back((Tile){val ? RED : BLACK, val});
        }
    }
}

Room::~Room()
{
}

void Room::Draw()
{
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            // if (tiles[x][y].collide)
            ::DrawRectangleLines (x*32,y*32,32,32,tiles[y][x].c);
        }
    }
}