#ifndef GAMEPLAY_COLLISION_CPP
#define GAMEPLAY_COLLISION_CPP

#include "GameplayTypes.cpp"
#include "../configs/Config.cpp"

int isArrowHitGhost(const Arrow& arrow, int ghostX, int ghostY) {
    int pixelSize = 3;
    int ghostLeft = ghostX + 2 * pixelSize;
    int ghostTop = ghostY - 46 * pixelSize;
    int ghostWidth = 26 * pixelSize;
    int ghostHeight = 46 * pixelSize;

    int ghostRight = ghostLeft + ghostWidth;
    int ghostBottom = ghostTop + ghostHeight;

    return (arrow.x >= ghostLeft && arrow.x <= ghostRight &&
            arrow.y >= ghostTop && arrow.y <= ghostBottom);
}

int isExplorerHitGhost(float explorerX, float explorerY, int ghostX, int ghostY) {
    int pixelSize = 3;
    int ghostLeft = ghostX + 2 * pixelSize;
    int ghostTop = ghostY - 46 * pixelSize;
    int ghostRight = ghostLeft + 26 * pixelSize;
    int ghostBottom = ghostTop + 46 * pixelSize;

    int explorerLeft = (int)explorerX - 30;
    int explorerRight = (int)explorerX + 30;
    int explorerTop = (int)explorerY - 90;
    int explorerBottom = (int)explorerY + 10;

    return !(explorerRight < ghostLeft || explorerLeft > ghostRight ||
             explorerBottom < ghostTop || explorerTop > ghostBottom);
}

int isExplorerHitFireball(float explorerX, float explorerY, float fireX, float fireY) {
    float dx = fireX - explorerX;
    float dy = fireY - (explorerY - 40.0f);
    return (dx * dx + dy * dy) <= 28.0f * 28.0f;
}

int isEnergyWaveHitGhost(const EnergyWave& wave, int ghostX, int ghostY) {
    int waveLeft = (wave.dir > 0) ? (int)wave.x : 0;
    int waveRight = (wave.dir > 0) ? SCREEN_WIDTH : (int)wave.x;
    int waveHalfH = 11;
    int waveTop = (int)wave.y - waveHalfH;
    int waveBottom = (int)wave.y + waveHalfH;

    int pixelSize = 3;
    int ghostLeft = ghostX + 2 * pixelSize;
    int ghostTop = ghostY - 46 * pixelSize;
    int ghostRight = ghostLeft + 26 * pixelSize;
    int ghostBottom = ghostTop + 46 * pixelSize;

    return !(waveRight < ghostLeft || waveLeft > ghostRight ||
             waveBottom < ghostTop || waveTop > ghostBottom);
}

int isArrowHitBoss(const Arrow& arrow, int bossX, int bossY) {
    int bossLeft = bossX - 95;
    int bossRight = bossX + 95;
    int bossTop = bossY - 230;
    int bossBottom = bossY + 40;

    return (arrow.x >= bossLeft && arrow.x <= bossRight &&
            arrow.y >= bossTop && arrow.y <= bossBottom);
}

int isEnergyWaveHitBoss(const EnergyWave& wave, int bossX, int bossY) {
    int waveLeft = (wave.dir > 0) ? (int)wave.x : 0;
    int waveRight = (wave.dir > 0) ? SCREEN_WIDTH : (int)wave.x;
    int waveHalfH = 11;
    int waveTop = (int)wave.y - waveHalfH;
    int waveBottom = (int)wave.y + waveHalfH;

    int bossLeft = bossX - 95;
    int bossRight = bossX + 95;
    int bossTop = bossY - 230;
    int bossBottom = bossY + 40;

    return !(waveRight < bossLeft || waveLeft > bossRight ||
             waveBottom < bossTop || waveTop > bossBottom);
}

int isExplorerHitBossAttack(float explorerX, float explorerY, float bossX, float bossY) {
    float dx = explorerX - bossX;

    // Đòn tấn công bay xa hết màn hình về phía bên trái của Boss
    if (dx < -40.0f) {
        // Buộc người chơi phải nhảy cao để né
        // Chiều cao bình thường là GROUND_Y + 30. Khi nhảy cao explorerY sẽ giảm xuống
        if (explorerY > GROUND_Y - 90.0f) {
            return 1;
        }
    }
    return 0;
}

#endif
