#ifndef CKEY_H
#define CKEY_H

#include <functional>
#include "led.hpp"
#include <EncButton2.h>
#include "usbkbd.hpp"

class KEY
{
    EncButton2<EB_BTN> button;
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
    this->button = EncButton2<EB_BTN>(INPUT_PULLUP, pin);
    this->key = NULL;
    this->keydown = [&]
    { this->nothing(); };
    this->keyup = [&]
    { this->nothing(); };
}

KEY::KEY(int pin, char *key)
{
    this->button = EncButton2<EB_BTN>(INPUT_PULLUP, pin);
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