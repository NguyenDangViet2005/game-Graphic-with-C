#ifndef LANGUAGE_EN_H
#define LANGUAGE_EN_H

#include "Language.h"

static const Language langEn = {
    // Main Menu
    "Play Game",                  // main_menu_play
    "Instructions",               // main_menu_instructions
    "Scoreboard",                 // main_menu_scoreboard
    "Settings",                   // main_menu_settings
    "Exit",                       // main_menu_exit

    // Common Buttons
    "Back",                       // back_button
    "Press ESC to return to menu", // esc_to_back

    // Settings Screen
    "SETTINGS",                   // settings_title
    "Sound",                      // settings_sound
    "ON",                         // settings_sound_on
    "OFF",                        // settings_sound_off
    "Language",                   // settings_language

    // Instructions Screen
    "GAME INSTRUCTIONS",                          // instructions_title
    "- ARROW keys: Move",                         // instructions_move
    "- SPACE key  : Attack",                      // instructions_attack
    "- SHIFT + ARROW: Dash/Move fast",            // instructions_dash
    "- CTRL + ARROW: Move slow + Shield",                  // instructions_slow
    "- SHIFT + SPACE : Power Attack",              // instructions_power
    "- C key       : Switch Weapon (Bow / Sword)", // instructions_weapon

    // Scoreboard Screen
    "SCOREBOARD",                 // scoreboard_title
    "No scores yet",              // scoreboard_empty

    // Pause Menu Overlay
    "PAUSED",                     // pause_title
    "Resume",                     // pause_resume
    "Exit to Menu",               // pause_exit_to_menu

    // HUD and Stats
    "HP:",                        // hud_hp
    "Score",                      // hud_score
    "Energy:",                    // hud_energy

    // Boss Info
    "REAPER BOSS",                             // boss_name_reaper
    "DEMON BOSS",                              // boss_name_demon
    "WARNING: REAPER BOSS IS SPAWNING!",       // boss_warning_reaper
    "WARNING: DEMON BOSS IS SPAWNING!",        // boss_warning_demon
    "DODGE!",                                  // boss_dodge

    // Loading Screen
    "Please wait...",             // loading_wait
    "Loading...",                 // loading_text
    "Loading forest...",          // loading_forest
    "Loading monsters...",        // loading_monsters
    "Complete...",                // loading_complete
    "Start!",                     // loading_start
    "Prepare for Adventure...",   // loading_subtitle

    // Game Over Screen
    "GAME OVER",                  // game_over_title
    "Score",                      // game_over_score
    "Main Menu",                  // game_over_to_menu

    // Spam Warning Screen
    "SPACE SPAM DETECTED",        // spam_title
    "Please slow down your SPACE presses.", // spam_message
    "Resume",                     // spam_button

    // Portal
    "ENTER TELEPORT PORTAL"       // portal_enter
};

#endif
