#include <raylib.h>

#include "button.hpp"

int main() {
    const int viewport_width{ 1280 };
    const int viewport_height{ 720 };

    InitWindow(viewport_width, viewport_height, "Button-test");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    const int fps{ 60 };
    SetTargetFPS(fps);

    Button button{
        Position{
            static_cast<float>(viewport_width) / 2,
            static_cast<float>(viewport_height) / 2
        },
        Size{ 200, 40 },
        AnchorPosition{ 100, 20 },
        BLACK, GRAY, RED, LIGHTGRAY
    };

    float dT{ 0.0f };
    while (WindowShouldClose() == false) {
        // ----------------------------------------------------------- update --
        dT = GetFrameTime();

        button.update(dT);

        // ------------------------------------------------------------- draw --
        BeginDrawing();

        ClearBackground(RAYWHITE);
        button.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
