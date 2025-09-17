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

    Room();
    ~Room();

    void Draw();
};

Room::Room()
{
    for (int i = 0; i < 10; ++i)
    {
        tiles.push_back(std::vector<Tile>());
        for (int j = 0; j < 10; ++j)
        {
            bool x = (i == 0 || i == 9 || j == 0 || j == 9);
            tiles[i].push_back((Tile){x ? RED : BLUE, x});
        }
    }
}

Room::~Room()
{
}

void Room::Draw()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            ::DrawRectangleLines(i*32,j*32,32,32,tiles[i][j].c);
        }
    }
}