#ifndef GAMEPLAY_COLLISION_CPP
#define GAMEPLAY_COLLISION_CPP

#include "GameplayTypes.cpp"

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

#endif
