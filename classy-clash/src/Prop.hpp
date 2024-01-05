#include "raylib.hpp"

class Prop {
public:

    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    auto getCollisionRec(Vector2 knightPos) -> Rectangle;

private:

    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};

};