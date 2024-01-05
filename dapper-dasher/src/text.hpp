#include "raylib.hpp"

struct Text {
    const char* text;
    int x;
    int y;
    int width;
    int height;
    raylib::Color color;

    Text(
        const char* text,
        int x,
        int y,
        int font_size,
        raylib::Color color
    ) : text(text), x(x), y(y), height(font_size), color(color) {
        this->width = raylib::MeasureText(this->text, this->height);
    }

    inline void draw() {
        raylib::DrawText(
            this->text,
            this->x,
            this->y,
            this->height,
            this->color
        );
    }
};