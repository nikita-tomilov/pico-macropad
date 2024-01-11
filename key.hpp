#ifndef CKEY_H
#define CKEY_H

#include <functional>
#include "led.hpp"
#include <EncButton.h>
#include "usbkbd.hpp"

class KEY
{
    Button button;
    char* key;

public:
    KEY(int pin);
    KEY(int pin, char* key);

    void tick();

    void nothing();

    std::function<void()> keydown;
    std::function<void()> keyup;
};


KEY::KEY(int pin)
{
    this->button = Button(pin, INPUT_PULLUP);
    this->key = NULL;
    this->keydown = [&]
    { this->nothing(); };
    this->keyup = [&]
    { this->nothing(); };
}

KEY::KEY(int pin, char *key)
{
    this->button = Button(pin, INPUT_PULLUP);
    this->key = key;
    this->keydown = [&]
    {
        // this->led->on();
        char code = *(this->key);
        keyDown(code);
    };
    this->keyup = [&]
    {
        // this->led->off();
        char code = *(this->key);
        keyUp(code);
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

#endif