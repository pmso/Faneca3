#pragma once

#include "Appstate.h"

struct MenuItem
{
    const char* text;
    Screen screen;
};

void MenuSetup();
void MenuLoop();