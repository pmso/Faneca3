#include "0000_Globals.h"

Screen currentScreen = SCREEN_MENU;

const MenuItem menuItems[] =
{
    { "FunkySSID", SCREEN_FUNKY_SSID },
    { "Morse Code", SCREEN_MORSE },
    { "TV Remote", SCREEN_TV_REMOTE },
    { "Settings", SCREEN_SETTINGS }
};

const int menuItemCount =
    sizeof(menuItems) / sizeof(menuItems[0]);

int selectedItem = 0;
int menuOffset = 0;

const int visibleItems = 3;


void initMenu()
{
    selectedItem = 0;
    menuOffset = 0;

    drawMenu();
}


void handleMenu()
{
    // Botão Central = Selecionar
    if (M5.BtnA.wasPressed())
    {
        changeScreen(menuItems[selectedItem].screen);
    }

    // Botão B = Próximo
    if (M5.BtnB.wasPressed())
    {
        selectedItem++;

        // Volta ao primeiro item
        if (selectedItem >= menuItemCount)
        {
            selectedItem = 0;
            menuOffset = 0;
        }

        // Faz scroll para baixo
        if (selectedItem >= menuOffset + visibleItems)
        {
            menuOffset++;
        }

        drawMenu();
    }
}


void drawMenu()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    M5.Display.setCursor(10, 10);
    M5.Display.println("Menu");

    for (int i = 0; i < visibleItems; i++)
    {
        int itemIndex = menuOffset + i;

        if (itemIndex >= menuItemCount)
            break;

        M5.Display.setCursor(10, 50 + (i * 30));

        if (itemIndex == selectedItem)
            M5.Display.print("> ");
        else
            M5.Display.print("  ");

        M5.Display.println(menuItems[itemIndex].name);
    }
}

void changeScreen(Screen newScreen)
{
    currentScreen = newScreen;

    switch (currentScreen)
    {
        case SCREEN_MENU:
            initMenu();
            break;

        case SCREEN_FUNKY_SSID:
            initFunkySSID();
            break;

        case SCREEN_MORSE:
            initMorseCode();
            break;

        case SCREEN_TV_REMOTE:
            initTVRemote();
            break;

        case SCREEN_SETTINGS:
            initSettings();
            break;
    }
}