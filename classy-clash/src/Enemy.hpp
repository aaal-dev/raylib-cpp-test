#include "raylib.hpp"
#include "BaseCharacter.hpp"
#include "Character.hpp"

class Enemy : public BaseCharacter {
public:

    Enemy(
        Vector2 pos,
        Texture2D idle_texture,
        Texture2D run_texture
    );
    virtual void tick(float deltaTime) override;
    virtual auto getScreenPos() -> Vector2 override;
    void setTarget(Character* character) { target = character; }

private:

    Character* target;
    float damagePerSec{ 10.0f };
    float radius{ 25.0f };

};