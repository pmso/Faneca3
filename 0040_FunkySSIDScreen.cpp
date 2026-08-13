#include "0000_Globals.h"
#include <WiFi.h>

const SSIDItem ssidList[] =
{
    { "FBI Surveillance Van", "" },
    { "Pretty Fly For A WiFi", "" },
    { "Free Pizza", "12345678" },
    { "Skynet", "judgementday" },
    { "Definitely Not Malware", "" },
    { "Hackers United", "password123" },
    { "2 Girls 1 Wifi", "" },
    { "Virus Distribution Center", "" },
    { "Wi-Fight Club", "firstrule" }
};

const int ssidCount =
    sizeof(ssidList) / sizeof(ssidList[0]);

const SSIDItem* currentSSID = nullptr;

void initFunkySSID()
{
    currentSSID = nullptr;

    WiFi.mode(WIFI_AP);
    WiFi.softAPdisconnect(true);

    drawFunkySSID();
}


void handleFunkySSID()
{
    // Botão A = gerar SSID
    if (M5.BtnA.wasPressed())
    {
        int randomIndex = random(ssidCount);

        currentSSID = &ssidList[randomIndex];

        if (currentSSID->password[0] == '\0')
        {
            WiFi.softAP(currentSSID->name);
        }
        else
        {
            WiFi.softAP(
                currentSSID->name,
                currentSSID->password
            );
        }

        drawFunkySSID();
    }

    // Botão B = voltar
    if (M5.BtnB.wasPressed())
    {
        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_OFF);

        changeScreen(SCREEN_MENU);
    }
}


void drawFunkySSID()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    M5.Display.setCursor(10, 10);
    M5.Display.println("FunkySSID");

    if (currentSSID == nullptr)
    {
        M5.Display.setCursor(10, 50);
        M5.Display.println("Press A");

        M5.Display.setCursor(10, 80);
        M5.Display.println("to start AP");
    }
    else
    {
        M5.Display.setCursor(10, 50);
        M5.Display.println("SSID:");

        M5.Display.setCursor(10, 75);
        M5.Display.println(currentSSID->name);

        if (currentSSID->password[0] == '\0')
        {
            M5.Display.setCursor(10, 105);
            M5.Display.println("OPEN");
        }
        else
        {
            M5.Display.setCursor(10, 105);
            M5.Display.println("Password:");

            M5.Display.setCursor(10, 130);
            M5.Display.println(currentSSID->password);
        }
    }

    M5.Display.setCursor(10, 170);
    M5.Display.println("A: New");

    M5.Display.setCursor(10, 195);
    M5.Display.println("B: Back");
}