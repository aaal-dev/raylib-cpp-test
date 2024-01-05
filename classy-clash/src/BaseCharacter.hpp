
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.hpp"

class BaseCharacter {
public:

    BaseCharacter();

    auto getAlive() -> bool { return alive; }
    auto getCollisionRec() -> Rectangle;
    auto getWorldPos() -> Vector2 { return worldPos; }
    void setAlive(bool isAlive) { alive = isAlive; }
    void undoMovement();
    
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;

protected:

    Texture2D idle {
        LoadTexture("../characters/knight_idle_spritesheet.png")
    };
    Texture2D run {
        LoadTexture("../characters/knight_run_spritesheet.png")
    };
    Texture2D texture {
        LoadTexture("../characters/knight_idle_spritesheet.png")
    };
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    // 1 : facing right, -1 : facing left
    float rightLeft{ 1.0f };
    // animation variables
    float runningTime{ 0.0f };
    float updateTime{ 1.0f / 12.0f };
    float speed{ 4.0f };
    float width{ 0.0f };
    float height{ 0.0f };
    float scale{ 4.0f };
    int frame{ 0 };
    int maxFrames{ 6 };

private:

    bool alive{ true };

};

#endif