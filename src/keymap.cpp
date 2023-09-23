#include "keymap.h"

void keyPressDetected()
{
    lastKeyPressTimestamp = millis();
}

void keyDown(uint8_t keycode)
{
    keyPressDetected();
    Keyboard.press(keycode);
    Serial.println(keycode);
}

void keyUp(uint8_t keycode)
{
    keyPressDetected();
    Keyboard.release(keycode);
}

void keyPress(uint8_t keycode)
{
    keyDown(keycode);
    delay(15);
    keyUp(keycode);
}

void consumerKeyPress(uint16_t keycode)
{
    keyPressDetected();
    Keyboard.consumerPress(keycode);
    delay(15);
    Keyboard.consumerRelease();
}
