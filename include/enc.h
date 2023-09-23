#ifndef CENC_H
#define CENC_H

#include <functional>
#include <EncButton2.h>

class ENC
{
    EncButton2<EB_ENCBTN> encoder;

public:
    ENC(int a, int b, int button);

    void tick();

    void nothing();

    std::function<void()> click;
    std::function<void()> left;
    std::function<void()> right;
    std::function<void()> leftH;
    std::function<void()> rightH;
};

#endif