#pragma once

#include "raylib-cpp.hpp"

#include <iostream>

namespace rl=raylib;

class TextureManager
{
private:
    rl::Texture2D tileTexture;
public:
    TextureManager();
    ~TextureManager();

    void DrawLevelTile(int tileIndex, int x, int y, int width, int height) const;
};

TextureManager::TextureManager()
{
    tileTexture = rl::Texture2D("assets/texture/dtiles.png");
}

TextureManager::~TextureManager()
{
}


void TextureManager::DrawLevelTile(int tileIndex, int x, int y, int width, int height) const {
    Rectangle source = (Rectangle) {(tileIndex % 8) * 32.0f, (tileIndex / 8) * 32.0f, (float)width,(float)height};
    Rectangle dest = (Rectangle) {(float)x,(float)y,32,32};
    tileTexture.Draw(source, dest);
}
