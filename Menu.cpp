#include "Globals.h"
#include "Menu.h"

const MenuItem menuItems[] =
{
    { "Funky SSID", SCREEN_FUNKY_SSID },
    { "Morse Code", SCREEN_MORSE },
    { "Settings",   SCREEN_SETTINGS }
};

const uint8_t MENU_SIZE = sizeof(menuItems) / sizeof(menuItems[0]);

uint8_t selectedItem = 0;

void DrawMenu()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);
    M5.Display.setCursor(10,5);
    M5.Display.println("MENU");

    for(uint8_t i = 0; i < MENU_SIZE; i++)
    {
        if(i==selected)
            M5.Display.printf("> %s\n", menuItems[i]);
        else
            M5.Display.printf("  %s\n", menuItems[i]);
    }
}

void MenuSetup()
{
    DrawMenu();
}

void MenuLoop()
{
    // Botão lateral
    if (M5.BtnA.wasPressed())
    {
        selectedItem++;

        if (selectedItem >= MENU_SIZE)
            selectedItem = 0;

        DrawMenu();
    }

    // Botão central
    if (M5.BtnPWR.wasPressed())
    {
        menuItems[selectedItem].screen;
    }
}