#include "FunkySSID.h"

const char* ssidList[] =
{
    "FBI Surveillance Van",
    "Pretty Fly For A WiFi",
    "Skynet",
    "Loading Virus...",
    "Free Pizza",
    "LAN Solo",
    "Hack Me If You Can",
    "404 Network Unavailable",
    "Definitely Not Malware"
};

const uint8_t SSID_COUNT = sizeof(ssidList) / sizeof(ssidList[0]);

uint8_t selectedSSID = 0;
bool apRunning = false;

void DrawScreen()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);
    M5.Display.setCursor(10, 5);
    M5.Display.println("Funky SSID");

    M5.Display.setTextSize(1);

    if (!apRunning)
    {
        M5.Display.println();
        M5.Display.printf("> %s\n", ssidList[selectedSSID]);

        M5.Display.println();
        M5.Display.println("BtnA  Next");
        M5.Display.println("BtnPWR Start");
    }
    else
    {
        M5.Display.println();
        M5.Display.println("Broadcasting:");

        M5.Display.println();
        M5.Display.println(ssidList[selectedSSID]);

        M5.Display.println();
        M5.Display.print("IP: ");
        M5.Display.println(WiFi.softAPIP());

        M5.Display.println();
        M5.Display.println("BtnPWR Stop");
    }
}

void FunkySSIDSetup()
{
    DrawScreen();
}

void StartAP()
{
    WiFi.mode(WIFI_AP);

    if (WiFi.softAP(ssidList[selectedSSID]))
    {
        apRunning = true;
    }
}

void StopAP()
{
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);

    apRunning = false;
}

void FunkySSIDLoop()
{
    if (!apRunning && M5.BtnA.wasPressed())
    {
        selectedSSID++;

        if (selectedSSID >= SSID_COUNT)
            selectedSSID = 0;

        DrawScreen();
    }

    if (M5.BtnPWR.wasPressed())
    {
        if (apRunning)
            StopAP();
        else
            StartAP();

        DrawScreen();
    }

    if (M5.BtnPWR.pressedFor(2000))
    {
        if (apRunning)
            StopAP();

        currentScreen = SCREEN_MENU;
    }
}