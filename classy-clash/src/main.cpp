#include "raylib.hpp"
#include "Character.hpp"
#include "Prop.hpp"
#include "Enemy.hpp"

#include <string>

int main()
{
    const int window_width{ 384 };
    const int window_height{ 384 };
    
    InitWindow(window_width, window_height, "Stephen's Top Down");

    Texture2D map = LoadTexture("../nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{ 0.0f, 0.0f };
    const float mapScale{ 4.0f };

    Character knight{ window_width, window_height };

    Prop props[2] {
        Prop {
            Vector2{ 600.f, 300.f },
            LoadTexture("../nature_tileset/Rock.png")
        },
        Prop {
            Vector2{ 400.f, 500.f },
            LoadTexture("../nature_tileset/Log.png")
        }
    };

    Enemy goblin {
        Vector2{ 800.f, 300.f },
        LoadTexture("../characters/goblin_idle_spritesheet.png"),
        LoadTexture("../characters/goblin_run_spritesheet.png")
    };

    Enemy slime {
        Vector2{ 500.f, 700.f },
        LoadTexture("../characters/slime_idle_spritesheet.png"),
        LoadTexture("../characters/slime_run_spritesheet.png")
    };

    Enemy *enemies[] {
        &goblin,
        &slime
    };

    for (auto enemy : enemies) {
        enemy->setTarget(&knight);
    }

    int fps{ 60 };
    SetTargetFPS(fps);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // draw the props
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }

        if (knight.getAlive() == true) {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        } else {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + window_width > map.width * mapScale ||
            knight.getWorldPos().y + window_height > map.height * mapScale)
        {
            knight.undoMovement();
        }
        // check prop collisions
        for (auto prop : props) {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies) {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (auto enemy : enemies) {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}