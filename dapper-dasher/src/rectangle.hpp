#include "raylib.hpp"

struct Rectangle {
    int x;
    int y;
    int width;
    int height;
    raylib::Color color;

    inline void draw() {
        raylib::DrawRectangle(
            this->x,
            this->y,
            this->width,
            this->height,
            this->color
        );
    }
};