#pragma once

#include <vector>
#include "room.h"

class World
{
private:
    std::vector<std::vector<Room>> roomsInWorld;
    int roomPosX;
    int roomPosY;
public:
    World();
    ~World();

    void DrawCurrentRoom();

    //-1 = left/up, 1 = right/down
    bool CheckIfSideRoomExists(int xMotion, int yMotion);
    //-1 = left/up, 1 = right/down
    void ChangeActiveRoom(int xMotion, int yMotion);

    CollisionResult CheckMovementCollision(int x, int y, int xToMove, int yToMove, int xSize=32, int ySize=32) const;

    static World LoadWorldFromFile(const std::string& fileName);
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

inline void World::DrawCurrentRoom()
{
    roomsInWorld[roomPosY][roomPosX].Draw();
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

inline World World::LoadWorldFromFile(const std::string &fileName)
{
    return World();
}
