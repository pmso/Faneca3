#include "0000_Globals.h"


void initTVRemote()
{
    drawTVRemote();
}


void handleTVRemote()
{
    // Botão B = voltar ao menu
    if (M5.BtnB.wasPressed())
    {
        changeScreen(SCREEN_MENU);
    }
}


void drawTVRemote()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    M5.Display.setCursor(10, 10);
    M5.Display.println("TVRemote");

    M5.Display.setCursor(10, 50);
    M5.Display.println("Coming soon");

    M5.Display.setCursor(10, 110);
    M5.Display.println("B: Back");
}