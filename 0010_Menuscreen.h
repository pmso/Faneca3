#pragma once
#include "0000_Globals.h"

enum Screen
{
    SCREEN_MENU,
    SCREEN_FUNKY_SSID,
    SCREEN_MORSE,
    SCREEN_TV_REMOTE,
    SCREEN_SETTINGS
};

struct MenuItem
{
    const char* name;
    Screen screen;
};

extern Screen currentScreen;

void initMenu();
void handleMenu();
void drawMenu();

void changeScreen(Screen newScreen);
