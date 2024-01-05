#include "background.hpp"
#include "circle.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "raylib.hpp"
#include "rectangle.hpp"
#include "text.hpp"

enum class GameState {
    MENU,
    GAME,
    LOSE
};

int main() {
    const int viewport_width{ 384 };
    const int viewport_height{ 216 };

    raylib::InitWindow(viewport_width, viewport_height, "Dasher");
    //raylib::SetWindowState(raylib::FLAG_WINDOW_RESIZABLE);

    // -------------------------------------------------------------------------
    Text game_over_text { "Game Over!", 0, 0, 40, raylib::MAROON };
    game_over_text.x = viewport_width / 2 - game_over_text.width / 2;
    game_over_text.y = viewport_height / 2 - game_over_text.height / 2;
    Rectangle game_over_text_bg {
        game_over_text.x - 20,
        game_over_text.y - 10,
        game_over_text.width + 40,
        game_over_text.height + 18,
        raylib::BLACK
    };

    // -------------------------------------------------------------------------
    Text restart_text { "Press «R» to continue", 0, 0, 20, raylib::RAYWHITE };
    restart_text.x = viewport_width / 2 - restart_text.width / 2;
    restart_text.y = viewport_height / 2 - restart_text.height / 2 + 60;
    float restart_text_update_time { 1.0f };
    float restart_text_running_time { 0.0f };
    bool restart_text_show { true };

    // -------------------------------------------------------------------------
    raylib::Texture2D player_texture = raylib::LoadTexture(
        "../textures/doux.png"
    );

    raylib::Vector2 player_default_position = {
            0.0f,
            static_cast<float>((viewport_height - player_texture.height))
    };
    Player player{
        player_texture,
        raylib::Rectangle{
            0.0f,
            0.0f,
            (static_cast<float>(player_texture.width) / 24),
            static_cast<float>(player_texture.height)
        },
        player_default_position,
        3.0f
    };

    // -------------------------------------------------------------------------
    raylib::Texture2D enemy_texture = raylib::LoadTexture(
        "../textures/nebula.png"
    );

    raylib::Vector2 enemy_default_position {
        viewport_width - 200,
        (viewport_height - (static_cast<float>(enemy_texture.height) / 8))
    };
    Enemy enemy{
        enemy_texture,
        raylib::Rectangle{
            0.0f,
            0.0f,
            (static_cast<float>(enemy_texture.width) / 8),
            (static_cast<float>(enemy_texture.height) / 8)
        },
        enemy_default_position
    };

    // -------------------------------------------------------------------------
    // -- BACKGROUND --
    // -------------------------------------------------------------------------
    raylib::Texture2D plx_tex_1 = raylib::LoadTexture(
        "../textures/parallax/plx-1.png"
    );
    raylib::Texture2D plx_tex_2 = raylib::LoadTexture(
        "../textures/parallax/plx-2.png"
    );
    raylib::Texture2D plx_tex_3 = raylib::LoadTexture(
        "../textures/parallax/plx-3.png"
    );
    raylib::Texture2D plx_tex_4 = raylib::LoadTexture(
        "../textures/parallax/plx-4.png"
    );
    raylib::Texture2D plx_tex_5 = raylib::LoadTexture(
        "../textures/parallax/plx-5.png"
    );
    
    BackGround plx_1(
        plx_tex_1,
        raylib::Vector2{ 0.0f, 0.0f },
        0.0f
    );

    BackGround plx_2(
        plx_tex_2,
        raylib::Vector2{ 0.0f, 0.0f },
        0.05f
    );

    BackGround plx_3(
        plx_tex_3,
        raylib::Vector2{ 0.0f, 0.0f },
        0.1f
    );

    BackGround plx_4(
        plx_tex_4,
        raylib::Vector2{ 0.0f, 0.0f },
        0.30f
    );

    BackGround plx_5(
        plx_tex_5,
        raylib::Vector2{ 0.0f, 0.0f },
        1.0f
    );

    // -------------------------------------------------------------------------
    // -- GAMELOOP --
    // -------------------------------------------------------------------------
    GameState game_state { GameState::GAME };

    int gravity{ 6000 };

    int fps{ 60 };
    raylib::SetTargetFPS(fps);

    float dT{ raylib::GetFrameTime() };

    while (raylib::WindowShouldClose() == false) {
        dT = raylib::GetFrameTime();

        raylib::BeginDrawing();
        raylib::ClearBackground(raylib::RAYWHITE);

        plx_1.draw();
        plx_2.draw();
        plx_3.draw();
        plx_4.draw();
        plx_5.draw();

        player.reset();

        switch (game_state) {
            case GameState::MENU: {
                break;
            }
            case GameState::GAME: {
                if (player.isOnGround(viewport_height) == false) {
                    player.velocity.y += gravity * dT;
                }

                bool crouch_key_pressed = raylib::IsKeyDown(raylib::KEY_S) ||
                                          raylib::IsKeyDown(raylib::KEY_DOWN);
                if (crouch_key_pressed) {
                    player.crouch();
                }

                bool jump_key_pressed = raylib::IsKeyPressed(raylib::KEY_SPACE) ||
                                        raylib::IsKeyPressed(raylib::KEY_W) ||
                                        raylib::IsKeyPressed(raylib::KEY_UP);
                if (jump_key_pressed) {
                    player.jump();
                }

                bool move_left_key_pressed = raylib::IsKeyDown(raylib::KEY_A) ||
                                             raylib::IsKeyDown(raylib::KEY_LEFT);
                if (move_left_key_pressed) {
                    //if (player.position.x > viewport_width * 4 / 10) {
                        player.moveLeft();
                    //} else {
                        plx_1.moveLeft(player.move_speed);
                        plx_2.moveLeft(player.move_speed);
                        plx_3.moveLeft(player.move_speed);
                        plx_4.moveLeft(player.move_speed);
                        plx_5.moveLeft(player.move_speed);
                        enemy.moveRight(player.move_speed);
                    //}
                }

                bool move_right_key_pressed = raylib::IsKeyDown(raylib::KEY_D) ||
                                              raylib::IsKeyDown(raylib::KEY_RIGHT);
                if (move_right_key_pressed) {
                    //if (player.position.x < viewport_width * 4 / 10) {
                        player.moveRight();
                    //} else {
                        plx_1.moveRight(player.move_speed);
                        plx_2.moveRight(player.move_speed);
                        plx_3.moveRight(player.move_speed);
                        plx_4.moveRight(player.move_speed);
                        plx_5.moveRight(player.move_speed);
                        enemy.moveLeft(player.move_speed);
                    //}
                }

                

                if (player.position.x + player.rect.width > enemy.position.x &&
                    player.position.x < enemy.position.x + enemy.rect.width &&
                    player.position.y + player.rect.height > enemy.position.y &&
                    player.position.y < enemy.position.y + enemy.rect.height) {
                        game_state = GameState::LOSE;
                }

                player.draw();
                enemy.draw();
                break;
            } 
            case GameState::LOSE: {
                constexpr float bg_move_speed { 200.0f };
                plx_1.moveRight(bg_move_speed);
                plx_2.moveRight(bg_move_speed);
                plx_3.moveRight(bg_move_speed);
                plx_4.moveRight(bg_move_speed);
                plx_5.moveRight(bg_move_speed);

                game_over_text_bg.draw();
                game_over_text.draw();

                restart_text_running_time += dT;
                if (restart_text_running_time > restart_text_update_time) {
                    restart_text_running_time = 0.0f;
                    restart_text_show = !restart_text_show;
                }

                if (restart_text_show) {
                    restart_text.draw();
                }

                if (raylib::IsKeyDown(raylib::KEY_R)) {
                    restart_text_running_time = 0.0f;
                    player.position = player_default_position;
                    enemy.position = enemy_default_position;
                    game_state = GameState::GAME;
                    restart_text_show = true;
                }
                
                break;
            }
        }

        plx_1.update(dT);
        plx_2.update(dT);
        plx_3.update(dT);
        plx_4.update(dT);
        plx_5.update(dT);

        player.update(dT);
        enemy.update(dT);

        raylib::EndDrawing();
    }

    raylib::UnloadTexture(plx_tex_5);
    raylib::UnloadTexture(plx_tex_4);
    raylib::UnloadTexture(plx_tex_3);
    raylib::UnloadTexture(plx_tex_2);
    raylib::UnloadTexture(plx_tex_1);
    raylib::UnloadTexture(enemy_texture);
    raylib::UnloadTexture(player_texture);
    raylib::CloseWindow();
}
