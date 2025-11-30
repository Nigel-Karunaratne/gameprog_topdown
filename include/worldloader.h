#pragma once

#include "world.h"
#include "room.h"

#include <memory>
#include <string>
#include <string_view>
#include <fstream>

#include "json.hpp"

#include <iostream>

using json = nlohmann::json;

class WorldLoader
{
public:
    WorldLoader() {};
    ~WorldLoader() {};

    static std::unique_ptr<World> LoadFromFile(std::string_view level_name);
};

std::unique_ptr<World> WorldLoader::LoadFromFile(std::string_view level_name)
{
    std::ifstream file(level_name.data());
    World* world = new World();

    if(file.is_open())
    {
        json data = json::parse(file);

        for (auto& l : data["partitions"])
        {
            Room room = Room();
            int x = l["x"];
            int y = l["y"];
            int pos = 0;
            for (auto& tile : l["data"]) {
                // std::cout << " add " << tile << std::endl;
                bool collide = tile > 0 && tile != 4;
                int t = static_cast<int>(tile) - 1;
                room.insertTileAt(pos++, (Tile) { t, collide } );
            }
            std::cout << "Going to add room...:" << std::endl; 
            world->SetupAddRoom(room, x, y);
        }

        std::cout << "done" << std::endl;
        world->debug_print();
    }

    return std::unique_ptr<World>(world);
}

