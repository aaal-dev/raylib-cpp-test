#include "raylib.hpp"

struct Circle {
    int x;
    int y;
    int radius;
    raylib::Color color;

    inline void draw() {
        raylib::DrawCircle(
            this->x,
            this->y,
            this->radius,
            this->color
        );
    }
};