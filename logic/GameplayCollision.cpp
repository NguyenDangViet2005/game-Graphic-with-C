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
    if (wave.type == 1) {
        int pixelSize = 3;
        int ghostLeft = ghostX + 2 * pixelSize;
        int ghostRight = ghostLeft + 26 * pixelSize;
        int strikeLeft = (wave.dir > 0) ? ((int)wave.x - 220) : 0;
        int strikeRight = (wave.dir > 0) ? SCREEN_WIDTH : ((int)wave.x + 220);
        return !(strikeRight < ghostLeft || strikeLeft > ghostRight);
    }

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
    if (wave.type == 1) {
        int bossLeft = bossX - 95;
        int bossRight = bossX + 95;
        int strikeLeft = (wave.dir > 0) ? ((int)wave.x - 220) : 0;
        int strikeRight = (wave.dir > 0) ? SCREEN_WIDTH : ((int)wave.x + 220);
        return !(strikeRight < bossLeft || strikeLeft > bossRight);
    }

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

int isExplorerHitBossAttack(float explorerX, float explorerY, float bossX, float bossY, float progress) {
    // Vị trí ngang hiện tại của luồng sóng năng lượng chém ra
    float cx = bossX - 40.0f - (progress * (bossX + 100.0f));
    
    // Khoảng cách giữa luồng năng lượng và Explorer
    float dx = cx - explorerX;

    // Đòn tấn công chém quét qua Explorer (mở rộng bề ngang)
    if (dx >= -75.0f && dx <= 75.0f) {
        // Buộc người chơi phải nhảy cao để né
        if (explorerY > GROUND_Y - 140.0f) {
            return 1;
        }
    }
    return 0;
}

int isSwordHitGhost(float explorerX, float explorerY, int facingRight, int ghostX, int ghostY) {
    int pixelSize = 3;
    int ghostLeft = ghostX + 2 * pixelSize;
    int ghostTop = ghostY - 46 * pixelSize;
    int ghostRight = ghostLeft + 26 * pixelSize;
    int ghostBottom = ghostTop + 46 * pixelSize;

    int swordLeft = facingRight ? (int)explorerX : (int)explorerX - 110;
    int swordRight = facingRight ? (int)explorerX + 110 : (int)explorerX;
    int swordTop = (int)explorerY - 90;
    int swordBottom = (int)explorerY + 20;

    return !(swordRight < ghostLeft || swordLeft > ghostRight ||
             swordBottom < ghostTop || swordTop > ghostBottom);
}

int isSwordHitBoss(float explorerX, float explorerY, int facingRight, int bossX, int bossY) {
    int bossLeft = bossX - 95;
    int bossRight = bossX + 95;
    int bossTop = bossY - 230;
    int bossBottom = bossY + 40;

    int swordLeft = facingRight ? (int)explorerX : (int)explorerX - 110;
    int swordRight = facingRight ? (int)explorerX + 110 : (int)explorerX;
    int swordTop = (int)explorerY - 90;
    int swordBottom = (int)explorerY + 20;

    return !(swordRight < bossLeft || swordLeft > bossRight ||
             swordBottom < bossTop || swordTop > bossBottom);
}

int isSwordHitFireball(float explorerX, float explorerY, int facingRight, float fireX, float fireY) {
    int swordLeft = facingRight ? (int)explorerX : (int)explorerX - 110;
    int swordRight = facingRight ? (int)explorerX + 110 : (int)explorerX;
    int swordTop = (int)explorerY - 90;
    int swordBottom = (int)explorerY + 20;

    return (fireX >= swordLeft && fireX <= swordRight &&
            fireY >= swordTop && fireY <= swordBottom);
}

#endif
