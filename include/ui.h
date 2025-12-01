#pragma once

#include "raylib-cpp.hpp"
#include <string>

namespace rl=raylib;

class UI
{
private:
public:
    UI();
    ~UI();

    void Draw(int playerHP);
};

UI::UI()
{
}

UI::~UI()
{
}

inline void UI::Draw(int playerHP)
{
    ::DrawRectangle(0, 256, 320, 32, BLACK);
    rl::Text hpText = rl::Text("hp: ",20, rl::Color::White(), ::GetFontDefault(), 1.5f);
    hpText.Draw(32, 320-60);
    rl::Text hpValueText = rl::Text(std::to_string(playerHP), 20);
    hpValueText.Draw(32 + hpText.MeasureEx().GetX(), 320-60);
}
