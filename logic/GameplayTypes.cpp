#ifndef GAMEPLAY_TYPES_CPP
#define GAMEPLAY_TYPES_CPP

struct Vec2 {
    float x;
    float y;
};

struct Arrow {
    float x;
    float y;
    float vx;
    float vy;
    float angle;
    float scale;
    int active;
};

struct GhostEnemy {
    float x;
    float y;
    float vx;
    float shootTimer;
    int hp;
    int active;
};

struct Fireball {
    float x;
    float y;
    float vx;
    float vy;
    int active;
};

struct EnergyWave {
    float x;
    float y;
    int dir;
    float life;
    int active;
};

static const int MAX_ARROWS = 6;
static const int MAX_GHOSTS = 4;
static const int MAX_FIREBALLS = 10;
static const int MAX_ENERGY_WAVES = 3;

Vec2 applyAffine(const Vec2& p, float cosA, float sinA, float sx, float sy, float tx, float ty) {
    Vec2 scaled = {p.x * sx, p.y * sy};
    Vec2 rotated = {scaled.x * cosA - scaled.y * sinA, scaled.x * sinA + scaled.y * cosA};
    Vec2 out = {rotated.x + tx, rotated.y + ty};
    return out;
}

#endif
