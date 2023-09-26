#ifndef CENC_H
#define CENC_H

#include <functional>
#include <EncButton2.h>

class ENC
{
    EncButton2<EB_ENCBTN> encoder;
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

#endif