#ifndef CENC_H
#define CENC_H

#include <functional>
#include <EncButton.h>
#include "usbkbd.hpp"

class ENC
{
    EncButton encoder;
    uint16_t* specifier;
    bool reversed = false;

public:
    ENC(int a, int b, int button);
    ENC(int a, int b, int button, uint16_t* specifier);

    void tick();

    void nothing();

    std::function<void()> click;
    std::function<void()> left;
    std::function<void()> right;
    std::function<void()> leftH;
    std::function<void()> rightH;
};

ENC::ENC(int a, int b, int button)
{
    this->encoder = EncButton(a, b, button, INPUT_PULLUP, INPUT_PULLUP);
    this->click = [&]
    { this->nothing(); };
    this->left = [&]
    { this->nothing(); };
    this->right = [&]
    { this->nothing(); };
    this->leftH = [&]
    { this->nothing(); };
    this->rightH = [&]
    { this->nothing(); };
}

ENC::ENC(int a, int b, int button, uint16_t *specifier)
{
    this->encoder = EncButton(a, b, button, INPUT_PULLUP, INPUT_PULLUP);
    this->specifier = specifier;

    this->click = [&]
    {
        int type = this->specifier[0];
        uint16_t code = this->specifier[3];
        if (type == CONSUMER)
        {
            consumerKeyPress(code);
        }
        else
        {
            keyPress(code);
        }
    };

    this->left = [&]
    {
        int type = this->specifier[0];
        uint16_t code = this->specifier[1];
        if (type == CONSUMER)
        {
            consumerKeyPress(code);
        }
        else
        {
            keyPress(code);
        }
    };
    this->right = [&]
    {
        int type = this->specifier[0];
        uint16_t code = this->specifier[2];
        if (type == CONSUMER)
        {
            consumerKeyPress(code);
        }
        else
        {
            keyPress(code);
        }
    };
}

void ENC::tick()
{
    this->encoder.tick();

    if (this->encoder.click())
    {
        this->click();
    }

    if (this->encoder.left())
    {
        this->left();
    }

    if (this->encoder.leftH())
    {
        this->leftH();
    }

    if (this->encoder.right())
    {
        this->right();
    }

    if (this->encoder.rightH())
    {
        this->rightH();
    }

    if (this->encoder.right())
    {
        this->right();
    }

    if (this->encoder.encHolding())
    {
        this->reversed = !this->reversed;
        this->encoder.setEncReverse(reversed);
    }
}

void ENC::nothing()
{
}

#endif