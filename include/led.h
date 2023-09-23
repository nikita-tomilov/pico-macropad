#ifndef CLED_H
#define CLED_H

class LED
{
    int pin;
    int maxBrighness;

public:
    LED(int pin, int maxBrighness);

    void on();
    void off();
    void set(int percentage);
};

#endif