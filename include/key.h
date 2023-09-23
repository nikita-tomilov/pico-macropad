#ifndef CKEY_H
#define CKEY_H

#include <functional>
#include "led.h"
#include <EncButton2.h>

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

#endif