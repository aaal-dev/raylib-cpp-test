#include "raylib.h"

struct Circle {
    int x;
    int y;
    int radius;
    Color color;

    inline void draw() {
        DrawCircle(
            this->x,
            this->y,
            this->radius,
            this->color
        );
    }
};

struct Rect {
    int x;
    int y;
    int width;
    int height;
    Color color;

    inline void draw() {
        DrawRectangle(
            this->x,
            this->y,
            this->width,
            this->height,
            this->color
        );
    }
};

struct Text {
    int x;
    int y;
    int size;
    const char* text;
    Color color;

    inline void draw() {
        DrawText(
            this->text,
            this->x,
            this->y,
            this->size,
            this->color
        );
    }
};

int main() {
    int viewport_width{ 800 };
    int viewport_height{ 600 };

    InitWindow(viewport_width, viewport_height, "Kek");

    Circle circle{ 175, 100, 25, BLUE };
    Rect axe{ 300, 100, 50, 50, RED };
    Text game_over_text{ 400, 200, 40, "Game Over!", RED };

    int direction{ 10 };
    int circle_speed{ 10 };

    bool collision_with_axe{ false };

    int fps{ 60 };
    SetTargetFPS(fps);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        collision_with_axe = (circle.x + circle.radius > axe.x) 
            && (circle.x < axe.x + axe.width + circle.radius)
            && (circle.y + circle.radius > axe.y)
            && (circle.y < axe.y + axe.height + circle.radius);

        // Game logic begins
        if (collision_with_axe) {
            game_over_text.draw();
        } else {
            //move the axe
            axe.y += direction;

            if (axe.y + axe.height > viewport_height || axe.y < 0) {
                direction = -direction;
            }

            if (IsKeyDown(KEY_D) && circle.x + circle.radius < viewport_width) {
                circle.x += circle_speed;
            }

            if (IsKeyDown(KEY_A) && circle.x > circle.radius) {
                circle.x -= circle_speed;
            }

            if (IsKeyDown(KEY_W) && circle.y > circle.radius) {
                circle.y -= circle_speed;
            }

            if (IsKeyDown(KEY_S) && circle.y + circle.radius < viewport_height) {
                circle.y += circle_speed;
            }

            circle.draw();
            axe.draw();
        }

        // Game logic ends
        EndDrawing();
    }
}

