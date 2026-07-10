#pragma once

enum Screen
{
    SCREEN_NONE = -1,
    
    SCREEN_MENU,
    SCREEN_FUNKY_SSID,
    SCREEN_MORSE,
    SCREEN_SETTINGS
};

extern Screen currentScreen;