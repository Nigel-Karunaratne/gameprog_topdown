#include "texture.h"

TextureManager::TextureManager()
{
    textureFileNames.emplace_back("assets/texture/dtiles.png");

    // PLACEHOLDER TEXTURE at id=0
    loadedTextures.emplace_back(::GenImageChecked(32,32,16,16,PURPLE,BLACK));

    int texturesToLoadThisCall = textureFileNames.size();
    for (int i = 0; i < texturesToLoadThisCall; ++i)
    {
        if (!textureFileNames.empty())
        {
            try
            {
                loadedTextures.emplace_back(textureFileNames.front().c_str());
            }
            catch(const std::exception& e)
            {
                TraceLog(LOG_INFO, e.what());
            }
            textureFileNames.pop_front();
        }
    }
}

TextureManager::~TextureManager()
{
}

inline const rl::Texture2D &TextureManager::GetTextureWhole(int id)
{
    if (id < 0 || id > loadedTextures.size())
        return loadedTextures[id];
    return loadedTextures[id];
}

inline void TextureManager::DrawTextureSlice(int textureID, int textureX, int textureY, int x, int y)
{
    ::DrawTextureRec(loadedTextures[textureID], (Rectangle){(float)textureX, (float)textureY, 32, 32}, (Vector2){(float)x,(float)y}, WHITE);
}
