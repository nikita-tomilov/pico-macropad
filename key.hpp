#ifndef CKEY_H
#define CKEY_H

#include <functional>
#include "led.hpp"
#include <EncButton.h>
#include "usbkbd.hpp"

extern void actionPerformed();

class KEY
{
    Button button;
    char* key;

public:
    KEY(int pin, char* key);

    void tick();

    void nothing();

    bool isModifier();

    std::function<void()> keydown;
    std::function<void()> keyup;

    std::function<void()> defaultkeydown;
    std::function<void()> defaultkeyup;
};

KEY::KEY(int pin, char *key)
{
    this->button = Button(pin, INPUT_PULLUP);
    this->key = key;
    this->defaultkeydown = [&]
    {
        // this->led->on();
        char code = *(this->key);
        if (code > 0x00) {
          keyDown(code);
        }
    };
    this->defaultkeyup = [&]
    {
        // this->led->off();
        char code = *(this->key);
        if (code > 0x00) {
          keyUp(code);
        }
    };
    this->keydown = this->defaultkeydown;
    this->keyup = this->defaultkeyup;
}

void KEY::tick()
{
    this->button.tick();

    if (this->button.press())
    {
        actionPerformed();
        this->keydown();
    }

    if (this->button.release())
    {
        actionPerformed();
        this->keyup();
    }
}

void KEY::nothing()
{
}

bool KEY::isModifier() {
  char code = *(this->key);
  return (code == 0x00);
}

#endif