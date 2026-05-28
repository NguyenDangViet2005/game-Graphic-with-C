#ifndef GAMEPLAY_LOOP_CPP
#define GAMEPLAY_LOOP_CPP

#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "../components/index.cpp"
#include "../components/LoadingScreen.cpp"
#include "GameplayTypes.cpp"
#include "GameplayCollision.cpp"
#include "GameplayRender.cpp"

// Import các file logic đã được tách để tăng tính mô-đun
#include "GameplayInit.cpp"
#include "GameplayUpdate.cpp"
#include "GameplayRenderMain.cpp"

extern void* cachedGameBackground;

void playGame() {
    cleardevice();

    initGameBackground();

    GameState state;
    initGameState(state);

    setactivepage(state.page);
    setvisualpage(state.page);

    DWORD lastTick = GetTickCount();

    srand((unsigned int)GetTickCount());

    while (kbhit()) getch();
    while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);

    while (state.gameRunning) {
        DWORD now = GetTickCount();
        float dt = (now - lastTick) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        lastTick = now;

        state.dt = dt;
        state.timeSec = now * 0.001f;
        state.arrowPulse = (float)sin(now * 0.008f);
        state.wavePhase = now * 0.02f;

        handleGameEvents(state);

        if (state.bossState != 2) {
            updateExplorer(state);
            updateProjectiles(state);
            updateGhostsAndHazards(state);
        }

        updateBoss(state);

        if (state.spaceSpamStop) {
            stopRunLoop();
            showSpamWarningScreen();
            state.spaceSpamStop = 0;
            state.rapidSpaceCount = 0;
            state.lastSpacePressTime = state.timeSec;
        }

        if (state.hp <= 0) {
            appendScoreToFile(state.score);
            stopRunLoop();
            stopCurrentMusic();
            playDeath();
            showGameOverScreen(state.score);
            break;
        }

        drawGameplay(state);
        state.page = 1 - state.page;
        delay(10);
    }
}

#endif
