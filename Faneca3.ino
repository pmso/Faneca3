#include "Globals.h"

Screen currentScreen = SCREEN_MENU;
Screen previousScreen = SCREEN_NONE;

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Display.setRotation(1);
    M5.Display.setBrightness(128);
}

void loop()
{
    M5.update();

    // Executado apenas quando muda de ecrã
    if(currentScreen != previousScreen)
    {
        previousScreen = currentScreen;

        switch(currentScreen)
        {
            case SCREEN_MENU:
                MenuSetup();
                break;

            case SCREEN_FUNKY_SSID:
                FunkySSIDSetup();
                break;

            case SCREEN_MORSE:
                MorseSetup();
                break;

            case SCREEN_SETTINGS:
                SettingsSetup();
                break;
        }
    }

    // Executado continuamente
    switch(currentScreen)
    {
        case SCREEN_MENU:
            MenuLoop();
            break;

        case SCREEN_FUNKY_SSID:
            FunkySSIDLoop();
            break;

        case SCREEN_MORSE:
            MorseLoop();
            break;

        case SCREEN_SETTINGS:
            SettingsLoop();
            break;
    }
}