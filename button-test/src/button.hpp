#pragma once

#include <raylib.h>

enum ButtonState {
    NORMAL,
    HOVERED,
    PRESSED,
    DISABLED
};

using Position = Vector2;
using Size = Vector2;
using AnchorPosition = Vector2;

struct Button {
    Position position;
    Size size;
    Color normal_color;
    Color hovered_color;
    Color pressed_color;
    Color disabled_color;

private:

    AnchorPosition anchor_position{ 0.0f, 0.0f };
    ButtonState state{ NORMAL };
    bool collided{ false };
    Color color{ BLACK };

public:

    explicit Button (
        Position position,
        Size size,
        AnchorPosition anchor_position,
        Color normal_color,
        Color hovered_color,
        Color pressed_color,
        Color disabled_color
    );

    void draw();
    void update(float dT);

};