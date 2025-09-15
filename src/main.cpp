#include "vendor/rlcpp/raylib-cpp.hpp"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

namespace rl = raylib;

int main(void)
{
    rl::Window window = rl::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "TopDownGame Runtime", FLAG_WINDOW_RESIZABLE);
    window.SetTargetFPS(60);

    rl::RenderTexture2D viewportRenderTexture = LoadRenderTexture(800,600);
    viewportRenderTexture.GetTexture().SetFilter(TEXTURE_FILTER_POINT);


    int currentScreenWidth = SCREEN_WIDTH;
    int currentScreenHeight = SCREEN_HEIGHT;
    float scale = MIN((float)currentScreenWidth/800, (float)currentScreenHeight/600);

    while (!window.ShouldClose())
    {
        // Calculate scale for render texture scaling
        if (::GetScreenWidth() != currentScreenWidth || ::GetScreenHeight() != currentScreenHeight)
        {
            currentScreenWidth = ::GetScreenWidth();
            currentScreenHeight = ::GetScreenHeight();
            scale = MIN((float)currentScreenWidth/800, (float)currentScreenHeight/600);
        }
        
        viewportRenderTexture.BeginMode();
            ::ClearBackground(WHITE);

            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    ::DrawRectangleLines(i*32,j*32,32,32,RED);
                }
            }
        EndTextureMode();

        window.BeginDrawing();
            window.ClearBackground(BLACK);

            viewportRenderTexture.GetTexture().Draw((Rectangle){0.0f,0.0f,(float)viewportRenderTexture.texture.width, (float)-viewportRenderTexture.texture.height},
                (Rectangle){ (GetScreenWidth() - ((float)SCREEN_WIDTH * scale))*0.5f, (GetScreenHeight() - ((float)SCREEN_HEIGHT * scale)) * 0.5f, (float)SCREEN_WIDTH * scale,
                (float)SCREEN_HEIGHT * scale}, (Vector2){0,0}, 0.0f, WHITE);
        window.EndDrawing();
    }
    return 0;
}