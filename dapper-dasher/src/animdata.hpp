#include "raylib.hpp"

struct AnimeData {
    raylib::Rectangle rect;
    raylib::Vector2 position;
    int frame { 0 };
    float animation_running_time { 0.0f };
    float animation_update_time { 1.0f / 12.0f };
};