#include "0000_Globals.h"


void initSettings()
{
    drawSettings();
}


void handleSettings()
{
    // Botão B = voltar ao menu
    if (M5.BtnB.wasPressed())
    {
        changeScreen(SCREEN_MENU);
    }
}


void drawSettings()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    M5.Display.setCursor(10, 10);
    M5.Display.println("Settings");

    M5.Display.setCursor(10, 50);
    M5.Display.println("Coming soon");

    M5.Display.setCursor(10, 110);
    M5.Display.println("B: Back");
}