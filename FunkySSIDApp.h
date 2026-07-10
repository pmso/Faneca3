#pragma once
#include "Globals.h"
#include <WiFi.h>

struct SSIDItem
{
    const char* ssid;
    const char* password;
};

void FunkySSIDSetup();
void FunkySSIDLoop();