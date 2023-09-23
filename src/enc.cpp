#include "enc.h"
#include "keymap.h"

ENC::ENC(int a, int b, int button)
{
    this->encoder = EncButton2<EB_ENCBTN>(INPUT_PULLUP, a, b, button);
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

ENC::ENC(int a, int b, int button, int type, uint16_t left, uint16_t right, uint16_t press)
{
    this->encoder = EncButton2<EB_ENCBTN>(INPUT_PULLUP, a, b, button);
    this->codeLeft = left;
    this->codeRight = right;
    this->codePress = press;

    if (type == CONSUMER)
    {
        this->click = [&]
        {
            consumerKeyPress(this->codePress);
        };
        this->left = [&]
        {
            consumerKeyPress(this->codeLeft);
        };
        this->right = [&]
        {
            consumerKeyPress(this->codeRight);
        };
    }
    else if (type == NORMAL)
    {
        this->click = [&]
        {
            keyPress(this->codePress);
        };
        this->left = [&]
        {
            keyPress(this->codeLeft);
        };
        this->right = [&]
        {
            keyPress(this->codeRight);
        };
    }
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

    if (this->encoder.held()) {
        this->reversed = !this->reversed;
        this->encoder.setEncReverse(reversed);
    }
}

void ENC::nothing()
{
}