#pragma once

#include "raylib-cpp.hpp"

#include <iostream>

namespace rl=raylib;

class TextureManager
{
private:
    rl::Texture2D tileTexture;
    rl::Texture2D characterTexture;
public:
    TextureManager();
    ~TextureManager();

    void DrawLevelTile(int tileIndex, int x, int y, int width, int height) const;
    
    void DrawPlayerIdle(int direction, int xPos, int yPos) const;
    void DrawPlayerMoving(int direction, int frameCount, int xPos, int yPos) const;
};

TextureManager::TextureManager()
{
    tileTexture = rl::Texture2D("assets/texture/dtiles.png");
    characterTexture = rl::Texture2D("assets/texture/character.png");
}

TextureManager::~TextureManager()
{
}


void TextureManager::DrawLevelTile(int tileIndex, int x, int y, int width, int height) const {
    Rectangle source = (Rectangle) {(tileIndex % 8) * 32.0f, (tileIndex / 8) * 32.0f, (float)width,(float)height};
    Rectangle dest = (Rectangle) {(float)x,(float)y,32,32};
    tileTexture.Draw(source, dest);
}

inline void TextureManager::DrawPlayerIdle(int direction, int xPos, int yPos) const
{
    Rectangle source = (Rectangle) {direction * 32.0f, 0.0f, 32.0f, 32.0f};
    characterTexture.Draw(source, (Vector2){(float)xPos,(float)yPos});
}

inline void TextureManager::DrawPlayerMoving(int direction, int frameCount, int xPos, int yPos) const
{
    Rectangle source = (Rectangle) {direction * 32.0f, (1 + frameCount) * 32.0f, 32.0f, 32.0f};
    characterTexture.Draw(source, (Vector2){(float)xPos,(float)yPos});
}
