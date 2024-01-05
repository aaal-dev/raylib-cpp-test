#include "button.hpp"

Button::Button (
    Position position,
    Size size,
    AnchorPosition anchor_position,
    Color normal_color,
    Color hovered_color,
    Color pressed_color,
    Color disabled_color
) : size(size)
    , normal_color(normal_color)
    , hovered_color(hovered_color)
    , pressed_color(pressed_color)
    , disabled_color(disabled_color)
    , anchor_position(anchor_position)
{
    this->position.x = position.x - anchor_position.x;
    this->position.y = position.y - anchor_position.y;
}


void Button::draw() {
    switch (state) {
        case NORMAL:
            color = normal_color;
            break;
        case HOVERED:
            color = hovered_color;
            break;
        case PRESSED:
            color = pressed_color;
            break;
        case DISABLED:
            color = disabled_color;
            break;
        default: break;
    }

    DrawRectangle(position.x, position.y, size.x, size.y, color);
}

void Button::update(float dT) {
    Position mouse_position = GetMousePosition();
    if (mouse_position.x > position.x
    &&  mouse_position.x < position.x + size.x
    &&  mouse_position.y > position.y
    &&  mouse_position.y < position.y + size.y) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            state = PRESSED;
        } else {
            state = HOVERED;
        }
    } else {
        state = NORMAL;
    }
}