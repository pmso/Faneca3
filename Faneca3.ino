#include "0000_Globals.h"

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    randomSeed(esp_random());

    M5.Display.setRotation(1);
    M5.Display.setBrightness(128);
}

void loop()
{
    M5.update();

    switch(currentScreen)
     {
         case SCREEN_MENU:
             handleMenu();
             break;

         case SCREEN_FUNKY_SSID:
             handleFunkySSID();
             break;

         case SCREEN_MORSE:
             handleMorseCode();
             break;
             
         case SCREEN_TV_REMOTE:
             handleTVRemote();
             break;    

         case SCREEN_SETTINGS:
             handleSettings();
             break;
     }
}