#ifndef CLED_H
#define CLED_H

#include <Arduino.h>

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

LED::LED(int pin, int maxBrighness)
{
    this->pin = pin;
    this->maxBrighness = maxBrighness;
    pinMode(pin, OUTPUT_8MA);
}

void LED::on()
{
    analogWrite(this->pin, maxBrighness);
}

void LED::off()
{
    analogWrite(this->pin, 0);
}

void LED::set(int percentage)
{
    analogWrite(this->pin, maxBrighness * percentage / 100);
}

#endif