#include "0000_Globals.h"

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

const int morseMessageCount =
    sizeof(morseMessages) / sizeof(morseMessages[0]);


int selectedMorseMessage = 0;

bool morsePlaying = false;
int morsePosition = 0;

unsigned long morseNextAction = 0;

const int MORSE_UNIT = 120;
const int MORSE_FREQUENCY = 800;

void initMorseCode()
{
    selectedMorseMessage = 0;

    morsePlaying = false;
    morsePosition = 0;
    morseNextAction = 0;

    M5.Speaker.stop();

    drawMorseCode();
}


void handleMorseCode()
{
    // B = voltar
    if (M5.BtnB.wasPressed())
    {
        M5.Speaker.stop();

        morsePlaying = false;

        changeScreen(SCREEN_MENU);

        return;
    }

    // C = próxima mensagem
    if (M5.BtnC.wasPressed() && !morsePlaying)
    {
        selectedMorseMessage++;

        if (selectedMorseMessage >= morseMessageCount)
            selectedMorseMessage = 0;

        drawMorseCode();
    }

    // A = iniciar/parar
    if (M5.BtnA.wasPressed())
    {
        if (morsePlaying)
        {
            morsePlaying = false;
            M5.Speaker.stop();
        }
        else
        {
            morsePlaying = true;
            morsePosition = 0;
            morseNextAction = 0;
        }

        drawMorseCode();
    }

    if (morsePlaying)
    {
        playMorse();
    }
}


void drawMorseCode()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);

    M5.Display.setCursor(10, 10);
    M5.Display.println("Morse Code");

    M5.Display.setCursor(10, 50);
    M5.Display.println(
        morseMessages[selectedMorseMessage].name
    );

    M5.Display.setCursor(10, 80);

    if (morsePlaying)
        M5.Display.println("TRANSMITTING");
    else
        M5.Display.println("READY");

    M5.Display.setCursor(10, 130);
    M5.Display.println("A: Start");

    M5.Display.setCursor(10, 155);
    M5.Display.println("C: Next");

    M5.Display.setCursor(10, 180);
    M5.Display.println("B: Back");
}

const char* getMorseCode(char character)
{
    for (int i = 0; i < sizeof(morseTable) / sizeof(morseTable[0]); i++)
    {
        if (morseTable[i].character == character)
            return morseTable[i].code;
    }

    return "";
}

void playMorse()
{
    static const char* currentCode = nullptr;
    static int codePosition = 0;
    static char lastCharacter = 0;

    if (millis() < morseNextAction)
        return;

    const char* message =
        morseMessages[selectedMorseMessage].message;

    char currentCharacter = message[morsePosition];

    // Fim da mensagem
    if (currentCharacter == '\0')
    {
        morsePosition = 0;
        morseNextAction = millis() + MORSE_UNIT * 7;

        return;
    }

    // Espaço entre palavras
    if (currentCharacter == ' ')
    {
        M5.Speaker.stop();

        morsePosition++;
        morseNextAction = millis() + MORSE_UNIT * 7;

        return;
    }

    // Novo carácter
    if (currentCharacter != lastCharacter)
    {
        currentCode = getMorseCode(currentCharacter);
        codePosition = 0;
        lastCharacter = currentCharacter;
    }

    // Fim do carácter
    if (currentCode[codePosition] == '\0')
    {
        M5.Speaker.stop();

        morsePosition++;
        lastCharacter = 0;

        morseNextAction = millis() + MORSE_UNIT * 3;

        return;
    }

    char symbol = currentCode[codePosition];

    int duration;

    if (symbol == '.')
        duration = MORSE_UNIT;
    else
        duration = MORSE_UNIT * 3;

    M5.Speaker.tone(MORSE_FREQUENCY);

    morseNextAction = millis() + duration;

    codePosition++;

    // Parar o speaker depois da duração
    while (millis() < morseNextAction)
    {
        M5.update();
    }

    M5.Speaker.stop();

    morseNextAction = millis() + MORSE_UNIT;
}