#include "raylib.hpp"

struct Player {
    raylib::Texture2D texture;
    raylib::Rectangle rect;
    raylib::Vector2 position;
    raylib::Color tint { raylib::WHITE };
    raylib::Vector2 velocity { 0.0f };
    int frame { 0 };
    bool on_ground { true };
    const int move_speed{ 500 };

private:

    float animation_running_time { 0.0f };
    const float animation_update_time { 1.0f / 8.0f };
    const int jump_velocity{ -1100 }; 
    int left_bound { 0 };
    int right_bound { 800 };
    float tex_scale { 1.0f };
    int start_frame { 0 };
    int end_frame { 3 };
    bool crouched { false };

public:

    Player(
        raylib::Texture2D texture,
        raylib::Rectangle rect,
        raylib::Vector2 position,
        float tex_scale
    ) : texture(texture), rect(rect), position(position), tex_scale(tex_scale) {}

    inline void animate() {
        if (this->animation_running_time >= this->animation_update_time && this->on_ground) {
           this->animation_running_time = 0.0f;

           this->rect.x = (this->frame + this->start_frame) * this->rect.width; 

           this->frame++;
           if (this->frame + this->start_frame > this->end_frame) {
               this->frame = 0;
           }
        }
    }

    inline void crouch() {
        crouched = true;
        start_frame = 17;
        end_frame = 17;
    }

    inline void draw() {
        raylib::DrawTexturePro(
            this->texture,
            this->rect,
            (raylib::Rectangle){
                this->position.x,
                this->position.y,
                this->rect.width * tex_scale,
                this->rect.height * tex_scale
            },
            (raylib::Vector2){ 0, 0 },
            0.0f,
            this->tint
        );
    }

    inline bool isOnGround(int ground_level) {
        this->on_ground = ((int)(this->position.y + this->rect.height * tex_scale) >= ground_level);
        if (this->on_ground) {
            this->position.y = ground_level - this->rect.height * tex_scale;
            this->velocity.y = 0.0f;
        }
        return this->on_ground;
    }

    inline void jump() {
        if (this->on_ground) {
            this->velocity.y += this->jump_velocity;
        }
    }

    inline void moveLeft() {
        //if (this->position.x > left_bound) {
        //    this->velocity.x = -this->move_speed;
        //}
        if (crouched) {
            start_frame = 18;
            end_frame = 23;
        } else {
            start_frame = 4;
            end_frame = 9;
        }
    }

    inline void moveRight() {
        //if ((this->position.x + this->rect.width) < right_bound) {
        //    this->velocity.x = this->move_speed;
        //}
        if (crouched) {
            start_frame = 18;
            end_frame = 23;
        } else {
            start_frame = 4;
            end_frame = 9;
        }
        
    }

    inline void reset() {
        crouched = false;
        start_frame = 0;
        end_frame = 3;
    }

    inline void update(float dT) {
        this->animation_running_time += dT;
        this->position.x += this->velocity.x * dT;
        this->position.y += this->velocity.y * dT;

        this->velocity.x = 0.0f;

        this->animate();
    }
};