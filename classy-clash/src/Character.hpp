#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.hpp"
#include "BaseCharacter.hpp"

class Character : public BaseCharacter {
public:

    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual auto getScreenPos() -> Vector2 override;
    auto getWeaponCollisionRec() -> Rectangle { return weaponCollisionRec; }
    auto getHealth() const -> float { return health; }
    void takeDamage(float damage);

private:

    Texture2D weapon {
        LoadTexture("../characters/weapon_sword.png")
    };
    Rectangle weaponCollisionRec{};
    float health{ 100.f };
    int windowWidth{ 0 };
    int windowHeight{ 0 };

};

#endif
