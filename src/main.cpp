#include "raylib-cpp.hpp"

#include "input.h"
#include "player.h"
#include "textures.h"
#include "room.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 288

namespace rl = raylib;

int main(void)
{
    rl::Window window = rl::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "TopDownGame Runtime", FLAG_WINDOW_RESIZABLE);
    window.SetTargetFPS(60);

    rl::RenderTexture2D viewportRenderTexture = LoadRenderTexture(SCREEN_WIDTH,SCREEN_HEIGHT);
    viewportRenderTexture.GetTexture().SetFilter(TEXTURE_FILTER_POINT);

    Input input = Input();
    Player player = Player(rl::Vector2(64,64));

    Room room = Room();

    TextureManager textureManager = TextureManager();

    int currentScreenWidth = SCREEN_WIDTH;
    int currentScreenHeight = SCREEN_HEIGHT;
    float scale = MIN((float)currentScreenWidth/SCREEN_WIDTH, (float)currentScreenHeight/SCREEN_HEIGHT);

    while (!window.ShouldClose())
    {
        // Calculate scale for render texture scaling
        if (::GetScreenWidth() != currentScreenWidth || ::GetScreenHeight() != currentScreenHeight)
        {
            currentScreenWidth = ::GetScreenWidth();
            currentScreenHeight = ::GetScreenHeight();
            scale = MIN((float)currentScreenWidth/SCREEN_WIDTH, (float)currentScreenHeight/SCREEN_HEIGHT);
        }

        player.Update(input, room);
        
        viewportRenderTexture.BeginMode();
            ::ClearBackground(WHITE);
            room.Draw();
            player.Draw();

            window.DrawFPS(16, 16);
        viewportRenderTexture.EndMode();

        window.BeginDrawing();
            window.ClearBackground(BLACK);

            viewportRenderTexture.GetTexture().Draw((Rectangle){0.0f,0.0f,(float)viewportRenderTexture.texture.width, (float)-viewportRenderTexture.texture.height},
                (Rectangle){ (GetScreenWidth() - ((float)SCREEN_WIDTH * scale))*0.5f, (GetScreenHeight() - ((float)SCREEN_HEIGHT * scale)) * 0.5f, (float)SCREEN_WIDTH * scale,
                (float)SCREEN_HEIGHT * scale}, (Vector2){0,0}, 0.0f, WHITE);
        window.EndDrawing();
    }
    return 0;
}