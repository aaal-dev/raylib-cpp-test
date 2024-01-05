#include "raylib.hpp"

struct Enemy {
    raylib::Texture2D texture;
    raylib::Rectangle rect;
    raylib::Vector2 position;
    raylib::Vector2 velocity { 0.0f };
    raylib::Color tint { raylib::WHITE };
    int frame { 0 };
    int frame_x { 0 };
    int frame_y { 0 };

private:

    float animation_running_time { 0.0f };
    const float animation_update_time { 1.0f / 12.0f };

public:

    Enemy(
        raylib::Texture2D texture,
        raylib::Rectangle rect,
        raylib::Vector2 position
    ) : texture(texture), rect(rect), position(position) {}

    inline void draw() {
        raylib::DrawTextureRec(
            this->texture,
            this->rect,
            this->position,
            this->tint
        );
    }

    inline void moveLeft(float move_speed) {
        this->velocity.x = -move_speed;
    }

    inline void moveRight(float move_speed) {
        this->velocity.x = move_speed;
    }

    inline void update(float dT) {
        this->position.x += this->velocity.x * dT;
        this->velocity.x = 0.0f;

        if (this->position.x + this->rect.width < 0.0f) {
            this->position.x = 800.0f;
        }
        
        this->animation_running_time += dT;
        if (
            this->animation_running_time >= this->animation_update_time
        ) {
            this->animation_running_time = 0.0f;

            this->rect.x = this->frame_x * this->rect.width;
            this->rect.y = this->frame_y * this->rect.height; 

            this->frame_x++;
            if (this->frame_x > 7) {
                this->frame_x = 0;
                this->frame_y++;
                if (this->frame_y > 7) {
                    this->frame_y = 0;
                }
            }
            
            this->frame++;
            if (this->frame > 59) {
                this->frame = 0;
                this->frame_x = 0;
                this->frame_y = 0;
            }
        }
    }
};