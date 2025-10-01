#pragma once

#include "raylib-cpp.hpp"
namespace rl = raylib;

class Input
{
private:
    rl::Gamepad gamepad;
public:
    Input();
    ~Input();

    int GetAxisHorizontal() const;
    int GetAxisVertical() const;

    bool GetItem1Pressed() const;
    bool GetItem2Pressed() const;
};

Input::Input() : gamepad()
{
}

Input::~Input()
{
}

inline int Input::GetAxisHorizontal() const
{
    return (rl::Keyboard::IsKeyDown(KEY_LEFT) ? -1 : 0) + (rl::Keyboard::IsKeyDown(KEY_RIGHT) ? 1 : 0);
}

inline int Input::GetAxisVertical() const
{
    return (rl::Keyboard::IsKeyDown(KEY_UP) ? -1 : 0) + (rl::Keyboard::IsKeyDown(KEY_DOWN) ? 1 : 0);
}
