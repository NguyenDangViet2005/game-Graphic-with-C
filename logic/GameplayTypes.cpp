#ifndef GAMEPLAY_TYPES_CPP
#define GAMEPLAY_TYPES_CPP

#include "../configs/Config.cpp"

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
    int hitBoss;
    int type; // 0: Bow (laser), 1: Sword (giant falling sword)
};

struct BossAttack {
    float x;
    float y;
    float life;
    int active;
};

static const int MAX_ARROWS = 6;
static const int MAX_GHOSTS = 4;
static const int MAX_FIREBALLS = 10;
static const int MAX_ENERGY_WAVES = 3;

struct GameState {
    int hp;
    int score;
    int mana;
    int manaMax;
    int skillReady;
    int gameRunning;
    int pauseBtnX;
    int pauseBtnY;

    // Explorer variables
    float explorerX;
    float explorerY;
    float explorerVy;
    float explorerSpeed;
    float explorerVx;
    float explorerAccel;
    float explorerFriction;
    float jumpSpeed;
    float gravity;
    float groundY;
    float explorerScale;
    float walkTime;
    float armSwing;
    float headSway;
    float shootCooldown;
    float hurtCooldown;
    int facingRight;
    int slowShieldActive;
    int slowShieldWasActive;

    // Ghost spawn variables
    float ghostBaseY;
    float ghostSpawnTimer;
    float ghostSpawnMin;
    float ghostSpawnMax;

    // Projectiles and enemies
    Arrow arrows[MAX_ARROWS];
    GhostEnemy ghosts[MAX_GHOSTS];
    Fireball fireballs[MAX_FIREBALLS];
    EnergyWave energyWaves[MAX_ENERGY_WAVES];

    // ReaperBoss variables
    int bossState; // 0: None, 1: Warning, 2: Summoning, 3: Active
    float bossWarningTimer;
    float bossSummonTimer;
    float bossX;
    float bossY;
    int bossLevel;
    int bossHp;
    int bossMaxHp;
    int nextBossScore;
    float bossAttackCooldown;
    float bossAttackChargeTimer;
    float bossAttackActiveTimer;

    // Frame-rate and timing info
    float dt;
    float timeSec;
    float arrowPulse;
    float wavePhase;
    float lastSpacePressTime;
    int rapidSpaceCount;
    int spaceSpamStop;
    
    // Page for double buffering
    int page;

    // Weapon variables
    int currentWeapon;      // 0: Bow, 1: Sword
    int isSlashing;         // 1 if active slash, 0 otherwise
    float swordSlashTime;   // remaining time for slash animation
    float swordSlashDuration;

    // Demon Theme and Portal transition variables
    int isDemonTheme;       // 0: normal, 1: demon
    int showPortal;         // 0: hide, 1: show portal
    float portalX;
    float portalY;

    // Demon Boss Eruption Skill variables
    int bossAttackType;     // 0: Slash, 1: Lava Plumes
    float eruptionX[3];     // X coordinates of warning/eruption circles
};

Vec2 applyAffine(const Vec2& p, float cosA, float sinA, float sx, float sy, float tx, float ty) {
    Vec2 scaled = {p.x * sx, p.y * sy};
    Vec2 rotated = {scaled.x * cosA - scaled.y * sinA, scaled.x * sinA + scaled.y * cosA};
    Vec2 out = {rotated.x + tx, rotated.y + ty};
    return out;
}

#endif
