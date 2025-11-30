#pragma once

#include <vector>
#include "room.h"

#include "texturemanager.h"

#include <iostream>

class World
{
private:
    std::vector<std::vector<Room>> roomsInWorld;
    int roomPosX;
    int roomPosY;
public:
    World();
    ~World();

    void DrawCurrentRoom(const TextureManager& textureManager);

    //-1 = left/up, 1 = right/down
    bool CheckIfSideRoomExists(int xMotion, int yMotion);
    //-1 = left/up, 1 = right/down
    void ChangeActiveRoom(int xMotion, int yMotion);

    CollisionResult CheckMovementCollision(int x, int y, int xToMove, int yToMove, int xSize=32, int ySize=32) const;

    void SetupAddRoom(Room roomToAdd, int x, int y)
    {
        std::cout << "current sizes are: " << roomsInWorld.size() << ", " << y << std::endl; 
        if (roomsInWorld.size() <= y)
        {
            std::cout << "  ok so diff is: " << y - roomsInWorld.size() << ", and y is " << y << std::endl; 
            for (int diff = y - roomsInWorld.size(); diff <= y; diff++)
            {
                roomsInWorld.push_back(std::vector<Room>());
                std::cout << "add one" << std::endl; 
            }
        }
        std::cout << "passed y" << std::endl; 
        std::cout << "moving on..."<< std::endl;

        if (roomsInWorld[y].size() <= x)
        {
            std::cout << "  ok so diff is: " << x - roomsInWorld[y].size() << ", and x is " << x << std::endl; 
            for (int diff = x - roomsInWorld[y].size(); diff <= x; diff++)
                roomsInWorld[y].push_back(Room());
        }

        roomsInWorld[y][x] = roomToAdd;
        std::cout << "ROOM ADDED AT y:" << y << ", x:" << x << std::endl; 
    }

    void debug_print()
    {
        for (int y = 0; y < roomsInWorld.size(); y++)
        {
            for (int x = 0; x < roomsInWorld[y].size(); x++) {
                std::cout << "ROOM AT " << x << " " << y << ": ";
                roomsInWorld[y][x].debug_print();
            }
            std::cout << std::endl;
        }
    }
};

World::World()
{
    roomPosX = 0;
    roomPosY = 0;

    roomsInWorld = 
    {
        {Room(), Room()}
    };
}

World::~World()
{
}

inline void World::DrawCurrentRoom(const TextureManager& textureManager)
{
    roomsInWorld[roomPosY][roomPosX].Draw(textureManager);
}

inline bool World::CheckIfSideRoomExists(int xMotion, int yMotion)
{
    // std::cout << (roomPosX-xMotion < 0) << " " << (roomPosX+xMotion > roomsInWorld[roomPosY].size()) << " " << (roomPosX+xMotion > roomsInWorld[roomPosY+yMotion].size()) << std::endl;

    if (roomPosY+yMotion < 0 || roomPosY+yMotion > (int)roomsInWorld.size())
        return false;

    if (roomPosX+xMotion < 0 || roomPosX+xMotion > (int)roomsInWorld[roomPosY].size())
        return false;

    if (roomPosX+xMotion < 0 || roomPosX+xMotion > (int)roomsInWorld[roomPosY+yMotion].size())
        return false;
    
    return true;
}

inline void World::ChangeActiveRoom(int xMotion, int yMotion)
{
    roomPosX += xMotion;
    roomPosY += yMotion;
}

inline CollisionResult World::CheckMovementCollision(int x, int y, int xToMove, int yToMove, int xSize, int ySize) const
{
    return roomsInWorld[roomPosY][roomPosX].CheckMovementCollision(x,y,xToMove,yToMove,xSize,ySize);
}
