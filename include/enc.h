#ifndef CENC_H
#define CENC_H

#include <functional>
#include <EncButton2.h>

class ENC
{
    EncButton2<EB_ENCBTN> encoder;
    uint16_t codeLeft;
    uint16_t codeRight;
    uint16_t codePress;

public:
    ENC(int a, int b, int button);
    ENC(int a, int b, int button, bool isConsumerCode, uint16_t left, uint16_t right, uint16_t press);

    void tick();

    void nothing();

    std::function<void()> click;
    std::function<void()> left;
    std::function<void()> right;
    std::function<void()> leftH;
    std::function<void()> rightH;
};

#endif