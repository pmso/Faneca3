#include "Globals.h"

struct MorseMessage
{
    const char* name;
    const char* text;
};

const MorseMessage morseMessages[] =
{
    { "SOS",              "SOS" },
    { "Hello World",      "HELLO WORLD" },
    { "Send Pizza",       "SEND PIZZA" },
    { "Coffee Please",    "COFFEE PLEASE" },
    { "I Am Batman",      "I AM BATMAN" },
    { "Never Gonna...",   "NEVER GONNA GIVE YOU UP" },
    { "Game Over",        "GAME OVER" }
};

const uint8_t MESSAGE_COUNT =
    sizeof(morseMessages) / sizeof(morseMessages[0]);

uint8_t selectedMessage = 0;
bool transmitting = false;

void DrawScreen()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 5);
    M5.Display.println("Morse");

    M5.Display.setTextSize(1);

    const MorseMessage& msg = morseMessages[selectedMessage];

    if (!transmitting)
    {
        M5.Display.println();
        M5.Display.printf("> %s\n", msg.name);

        M5.Display.println();
        M5.Display.println("BtnA  Next");
        M5.Display.println("BtnPWR Send");
    }
    else
    {
        M5.Display.println();
        M5.Display.println("Sending:");

        M5.Display.println();
        M5.Display.println(msg.text);

        M5.Display.println();
        M5.Display.println("BtnPWR Stop");
    }
}

void MorseCodeSetup()
{
    DrawScreen();
}

void MorseCodeLoop()
{
    if (!transmitting && M5.BtnA.wasPressed())
    {
        selectedMessage++;

        if (selectedMessage >= MESSAGE_COUNT)
            selectedMessage = 0;

        DrawScreen();
    }

    if (M5.BtnPWR.wasPressed())
    {
        transmitting = !transmitting;
        DrawScreen();
    }

    if (M5.BtnPWR.pressedFor(2000))
    {
        transmitting = false;
        currentScreen = SCREEN_MENU;
    }
}