#include "raylib.hpp"

struct BackGround {
    raylib::Texture2D texture;
    raylib::Vector2 position[2];
    raylib::Vector2 size;
    raylib::Color tint { raylib::WHITE };

    float rotation { 0.0f };
    float scale { 1.0f };

private:

    float velocity { 0.0f };
    float move_speed_scale { 1.0f };

public:

    BackGround(
        raylib::Texture2D texture,
        raylib::Vector2 position,
        float move_speed_scale
    ) : texture(texture), move_speed_scale(move_speed_scale) {
        this->size.x = texture.width * this->scale;
        this->size.y = texture.height * this->scale;
        this->position[0] = position;
        this->position[1] = { position.x + this->size.x, position.y };
            
    }

    inline void draw() {
        raylib::DrawTextureEx(
            this->texture,
            this->position[0],
            this->rotation,
            this->scale,
            this->tint
        );
        raylib::DrawTextureEx(
            this->texture,
            this->position[1],
            this->rotation,
            this->scale,
            this->tint
        );
    }

    inline void moveLeft(float move_speed) {
        this->velocity = -move_speed;
    }

    inline void moveRight(float move_speed) {
        this->velocity = move_speed;
    }

    inline void update(float dT) {
        this->position[0].x -= velocity * move_speed_scale * dT;
        this->position[1].x -= velocity * move_speed_scale * dT;

        if(this->position[0].x + this->size.x < 0.0f) {
            this->position[0].x = this->position[1].x + this->size.x;
        } else if(this->position[0].x > 0.0f) {
            this->position[1].x = this->position[0].x - this->size.x;
        }
        
        if(this->position[1].x + this->size.x < 0.0f) {
            this->position[1].x = this->position[0].x + this->size.x;
        } else if(this->position[1].x > 0.0f) {
            this->position[0].x = this->position[1].x - this->size.x;
        }

        this->velocity = 0.0f;
    }
};