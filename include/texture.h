#pragma once

#include "raylib-cpp.hpp"
namespace rl = raylib;

#include <string>
#include <vector>
#include <deque>

class TextureManager
{
private:
    std::deque<std::string> textureFileNames;
    std::vector<rl::Texture2D> loadedTextures;

public:
    TextureManager();
    ~TextureManager(); //NOTE - raylib-cpp Texture2D handles unload w/ its destructor

    const rl::Texture2D& GetTextureWhole(int id);
    void DrawTextureSlice(int textureID, int textureX, int textureY, int x, int y);
};
