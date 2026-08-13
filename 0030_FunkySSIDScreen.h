#pragma once

struct SSIDItem
{
    const char* name;
    const char* password;
};

void initFunkySSID();
void handleFunkySSID();
void drawFunkySSID();