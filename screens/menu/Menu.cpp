#ifndef MENU_SCREEN_CPP
#define MENU_SCREEN_CPP

#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../configs/Config.cpp"
#include "../../configs/Audio.cpp"
#include "../../components/index.cpp"
#include "../../components/LoadingScreen.cpp"

void* cachedBackground = NULL;
void* cachedGameBackground = NULL;
void* cachedGhostSprite = NULL;
void* cachedGhostMask = NULL;
void* cachedFireballSprite = NULL;
void* cachedFireballMask = NULL;

#include "MenuCache.cpp"
#include "MenuScreens.cpp"
#include "../instruction/InstructionsScreen.cpp"
#include "../scoreboard/ScoreboardScreen.cpp"
#include "../settings/SettingsScreen.cpp"
#include "../../logic/GameplayTypes.cpp"
#include "../../logic/GameplayCollision.cpp"
#include "../../logic/GameplayRender.cpp"
#include "../../logic/GameplayLoop.cpp"
#include "MenuLoop.cpp"

#endif
    
