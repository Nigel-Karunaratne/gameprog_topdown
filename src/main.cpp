#include "vendor/raylib/raylib.h"
#include "vendor/raylib/raymath.h"        // Required for: Vector2Clamp()

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
    InitWindow(800,600,"TopDownGame Runtime");
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    RenderTexture2D viewportRenderTexture = LoadRenderTexture(800,600);
    SetTextureFilter(viewportRenderTexture.texture, TEXTURE_FILTER_POINT);

    while (!WindowShouldClose())
    {
        float scale = MIN((float)GetScreenWidth()/800, (float)GetScreenHeight()/600);
        
        BeginTextureMode(viewportRenderTexture);
            ClearBackground(WHITE);
            DrawText("Text on the Screen", 200, 200, 32, BLUE);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(viewportRenderTexture.texture, (Rectangle){0.0f,0.0f,(float)viewportRenderTexture.texture.width, (float)-viewportRenderTexture.texture.height},
            (Rectangle){ (GetScreenWidth() - ((float)SCREEN_WIDTH * scale))*0.5f, (GetScreenHeight() - ((float)SCREEN_HEIGHT * scale)) * 0.5f, (float)SCREEN_WIDTH * scale, (float)SCREEN_HEIGHT * scale}, (Vector2){0,0}, 0.0f, WHITE);
        EndDrawing();
    }
    return 0;
}