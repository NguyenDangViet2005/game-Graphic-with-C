#ifndef GAMEPLAY_INIT_CPP
#define GAMEPLAY_INIT_CPP

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "../components/index.cpp"
#include "../components/LoadingScreen.cpp"
#include "GameplayTypes.cpp"

extern void* cachedGameBackground;
extern void* cachedGhostSprite;
extern void* cachedGhostMask;
extern void* cachedFireballSprite;
extern void* cachedFireballMask;

static void appendScoreToFile(int score) {
    FILE* fp = fopen("scores.txt", "a");
    if (!fp) {
        return;
    }
    fprintf(fp, "%d\n", score);
    fclose(fp);
}

void updateGameBackgroundTheme(bool isDemonTheme) {
    if (cachedGameBackground == NULL) return;
    int oldActive = getactivepage();
    
    // Đặt Active Page sang trang tạm để vẽ ngầm
    int tempPage = 1 - oldActive;
    setactivepage(tempPage);
    cleardevice();
    
    if (isDemonTheme) {
        drawBackgroundDemon();
        drawDarkForestDemon();
    } else {
        drawBackground();
        drawDarkForest();
    }
    
    // Ghi đè vào cachedGameBackground
    getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedGameBackground);
    
    // Khôi phục lại Active Page
    setactivepage(oldActive);
}

static void initGameState(GameState& state) {
    state.hp = 3;
    state.score = 0;
    state.mana = 0;
    state.manaMax = 10;
    state.skillReady = 0;
    state.gameRunning = 1;
    state.pauseBtnX = SCREEN_WIDTH - 70;
    state.pauseBtnY = 20;

    state.explorerX = 200.0f;
    state.explorerY = (float)(GROUND_Y + 30);
    state.explorerVy = 0.0f;
    state.explorerSpeed = 280.0f;
    state.explorerVx = 0.0f;
    state.explorerAccel = 1600.0f;
    state.explorerFriction = 1400.0f;
    state.jumpSpeed = -620.0f;
    state.gravity = 1400.0f;
    state.groundY = (float)(GROUND_Y + 30);
    state.explorerScale = 1.0f;
    state.walkTime = 0.0f;
    state.armSwing = 0.0f;
    state.headSway = 0.0f;
    state.shootCooldown = 0.0f;
    state.hurtCooldown = 0.0f;
    state.facingRight = 1;
    state.slowShieldActive = 0;
    state.slowShieldWasActive = 0;

    state.ghostBaseY = (float)(GROUND_Y + 30);
    state.ghostSpawnTimer = 1.6f;
    state.ghostSpawnMin = 1.6f;
    state.ghostSpawnMax = 2.6f;

    for (int i = 0; i < MAX_ARROWS; i++) {
        state.arrows[i].active = 0;
    }
    for (int i = 0; i < MAX_GHOSTS; i++) {
        state.ghosts[i].active = 0;
    }
    for (int i = 0; i < MAX_FIREBALLS; i++) {
        state.fireballs[i].active = 0;
    }
    for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
        state.energyWaves[i].active = 0;
    }

    state.bossState = 0;
    state.bossWarningTimer = 0.0f;
    state.bossSummonTimer = 0.0f;
    state.bossX = 0.0f;
    state.bossY = 0.0f;
    state.bossLevel = 1;
    state.bossHp = 30;
    state.bossMaxHp = 30;
    state.nextBossScore = 2000;
    state.bossAttackCooldown = 3.0f;
    state.bossAttackChargeTimer = 0.0f;
    state.bossAttackActiveTimer = 0.0f;

    state.dt = 0.0f;
    state.timeSec = 0.0f;
    state.arrowPulse = 0.0f;
    state.wavePhase = 0.0f;
    state.lastSpacePressTime = 0.0f;
    state.rapidSpaceCount = 0;
    state.spaceSpamStop = 0;
    state.page = 0;

    // Weapon defaults
    state.currentWeapon = 0; // Bow by default
    state.isSlashing = 0;
    state.swordSlashTime = 0.0f;
    state.swordSlashDuration = 0.2f;

    // Demon Theme and Portal transition variables
    state.isDemonTheme = 0;
    state.showPortal = 0;
    state.portalX = 0.0f;
    state.portalY = 0.0f;

    // Demon Boss Eruption Skill variables
    state.bossAttackType = 0;
    state.eruptionX[0] = 0.0f;
    state.eruptionX[1] = 0.0f;
    state.eruptionX[2] = 0.0f;

    // Reset background to normal theme is now handled in initGameBackground
}

static void initGameBackground() {
    if (cachedGameBackground == NULL) {
        playMusicLoading();
        drawLoadingScreen(0, gCurrentLanguage->loading_wait);
        delay(150);

        int oldPage = getactivepage();
        setactivepage(1);
        cleardevice();

        setactivepage(0);
        drawLoadingScreen(20, gCurrentLanguage->loading_text);
        setactivepage(1);
        delay(80);

        drawBackground();

        setactivepage(0);
        drawLoadingScreen(55, gCurrentLanguage->loading_forest);
        setactivepage(1);
        delay(80);

        drawDarkForest();

        setactivepage(0);
        drawLoadingScreen(85, gCurrentLanguage->loading_monsters);
        setactivepage(1);
        delay(80);

        unsigned int size = imagesize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        cachedGameBackground = malloc(size);
        getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedGameBackground);

        // Pre-cache Ghost and Fireball sprites/masks for lag-free performance!
        int ghostW = 25 * 3;
        int ghostH = 46 * 3;
        unsigned int ghostSize = imagesize(0, 0, ghostW, ghostH);
        
        // Ghost Sprite
        cleardevice();
        drawGhost(-6, 138, 0);
        cachedGhostSprite = malloc(ghostSize);
        getimage(0, 0, ghostW, ghostH, cachedGhostSprite);
        
        // Ghost Mask
        cleardevice();
        drawGhost(-6, 138, 1);
        cachedGhostMask = malloc(ghostSize);
        getimage(0, 0, ghostW, ghostH, cachedGhostMask);

        int fireW = 11 * 3;
        int fireH = 11 * 3;
        unsigned int fireSize = imagesize(0, 0, fireW, fireH);
        
        // Fireball Sprite
        cleardevice();
        drawFireball(16, 16, 0);
        cachedFireballSprite = malloc(fireSize);
        getimage(0, 0, fireW, fireH, cachedFireballSprite);
        
        // Fireball Mask
        cleardevice();
        drawFireball(16, 16, 1);
        cachedFireballMask = malloc(fireSize);
        getimage(0, 0, fireW, fireH, cachedFireballMask);

        setactivepage(0);
        drawLoadingScreen(95, gCurrentLanguage->loading_complete);
        delay(100);

        drawLoadingScreen(100, gCurrentLanguage->loading_start);
        delay(400);

        putimage(0, 0, cachedGameBackground, COPY_PUT);
        setactivepage(oldPage);
        playMusicPlay();
    } else {
        // Nếu đã có cache (chơi lại), reset background về rừng tối trong lúc hiển thị màn hình loading nhanh
        playMusicLoading();
        drawLoadingScreen(20, gCurrentLanguage->loading_wait);
        delay(150);

        drawLoadingScreen(60, gCurrentLanguage->loading_text);
        
        // Thực hiện cập nhật background về trạng thái ban đầu trong lúc đang hiện loading
        updateGameBackgroundTheme(false);
        delay(100);

        drawLoadingScreen(100, gCurrentLanguage->loading_complete);
        delay(300);

        putimage(0, 0, cachedGameBackground, COPY_PUT);
        playMusicPlay();
    }
}

#endif
