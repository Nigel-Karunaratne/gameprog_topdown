#include "raylib-cpp.hpp"

#include "input.h"
#include "player.h"

#include "ui.h"

#include "world.h"
#include "worldloader.h"

#include "room.h"

#include "texturemanager.h"

#define DEBUG_ON

#ifdef DEBUG_ON
#include "../vendor/rlimgui/rlImGui.h"
#include "../vendor/imgui/imgui.h"
#endif

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 288

#include "iostream"

namespace rl = raylib;

int main(void)
{
    rl::Window window = rl::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "TopDownGame Runtime", FLAG_WINDOW_RESIZABLE);
    window.SetTargetFPS(60);

    rlImGuiSetup(true);

    rl::RenderTexture2D viewportRenderTexture = LoadRenderTexture(SCREEN_WIDTH,SCREEN_HEIGHT);
    viewportRenderTexture.GetTexture().SetFilter(TEXTURE_FILTER_POINT);

    Input input = Input();
    Player player = Player(rl::Vector2(64,64));

    UI ui = UI();

    WorldLoader* wl = new WorldLoader();
    World* world = wl->LoadFromFile("assets/room/main.json").release();

    world->debug_print();

    TextureManager textureManager = TextureManager();

    int currentScreenWidth = SCREEN_WIDTH;
    int currentScreenHeight = SCREEN_HEIGHT;
    float scale = MIN((float)currentScreenWidth/SCREEN_WIDTH, (float)currentScreenHeight/SCREEN_HEIGHT);

#ifdef DEBUG_ON
    int debugPlayerSpeed= player.GetSpeed();
    int debugHP = player.GetHP();
    bool stayOpen = true;
#endif

#ifdef DEBUG_ON
    while (!window.ShouldClose() && stayOpen)
#else
    while (!window.ShouldClose())
#endif
    {
        // Calculate scale for render texture scaling
        if (::GetScreenWidth() != currentScreenWidth || ::GetScreenHeight() != currentScreenHeight)
        {
            currentScreenWidth = ::GetScreenWidth();
            currentScreenHeight = ::GetScreenHeight();
            scale = MIN((float)currentScreenWidth/SCREEN_WIDTH, (float)currentScreenHeight/SCREEN_HEIGHT);
        }

        player.Update(window.GetFrameTime(), input, *world);
        
        viewportRenderTexture.BeginMode();
            ::ClearBackground(WHITE);
            world->DrawCurrentRoom(textureManager);
            ui.Draw(player.GetHP());
            player.Draw(textureManager);

            window.DrawFPS(16, 16);
        viewportRenderTexture.EndMode();

        window.BeginDrawing();
            window.ClearBackground(BLACK);

            viewportRenderTexture.GetTexture().Draw((Rectangle){0.0f,0.0f,(float)viewportRenderTexture.texture.width, (float)-viewportRenderTexture.texture.height},
                (Rectangle){ (GetScreenWidth() - ((float)SCREEN_WIDTH * scale))*0.5f, (GetScreenHeight() - ((float)SCREEN_HEIGHT * scale)) * 0.5f, (float)SCREEN_WIDTH * scale,
                (float)SCREEN_HEIGHT * scale}, (Vector2){0,0}, 0.0f, WHITE);

#ifdef DEBUG_ON
            rlImGuiBegin();
            ImGui::Begin("Debug Window");
            ImGui::SliderInt("Speed (player)", &debugPlayerSpeed, 0, 10);
            ImGui::SliderInt("HP (player)", &debugHP, 0, 7);
            ImGui::End();

            player.setSpeed(debugPlayerSpeed);
            player.setHP(debugHP);

            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("Debug")) {
                    if (ImGui::MenuItem("Exit")) { stayOpen = false; }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }
            rlImGuiEnd();
#endif
        window.EndDrawing();
    }

#ifdef DEBUG_ON
    rlImGuiShutdown();
#endif

    delete world;
    delete wl;
    
    return 0;
}