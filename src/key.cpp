#include "key.h"
#include "keymap.h"

KEY::KEY(int pin)
{
    this->button = EncButton2<EB_BTN>(INPUT_PULLUP, pin);
    this->led = new LED(-1, -1);
    this->key = 'a';
    this->keydown = [&]
    { this->nothing(); };
    this->keyup = [&]
    { this->nothing(); };
}

KEY::KEY(int pin, LED *led)
{
    this->button = EncButton2<EB_BTN>(INPUT_PULLUP, pin);
    this->led = led;
    this->key = 'a';
    this->keydown = [&]
    { this->led->on(); };
    this->keyup = [&]
    { this->led->off(); };
}

KEY::KEY(int pin, LED *led, char key)
{
    this->button = EncButton2<EB_BTN>(INPUT_PULLUP, pin);
    this->led = led;
    this->key = key;
    this->keydown = [&]
    {
        this->led->on();
        keyDown(this->key);
    };
    this->keyup = [&]
    {
        this->led->off();
        keyUp(this->key);
    };
}

void KEY::tick()
{
    this->button.tick();

    if (this->button.press())
    {
        this->keydown();
    }

    if (this->button.release())
    {
        this->keyup();
    }
}

void KEY::nothing()
{
}