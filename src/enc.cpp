#include "enc.h"

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
}

void ENC::nothing()
{
}