#ifndef CENC_H
#define CENC_H

#include <functional>
#include <EncButton.h>
#include "usbkbd.hpp"

extern void sendControlMessage(byte channel, byte controlNumber, byte value);
extern void actionPerformed();

class ENC
{
    EncButton encoder;
    uint16_t* specifier;
    bool reversed = false;

    byte midiControlNumbers[2];
    byte midiValues[2] = {64, 64};
    byte midiLayer = 0;

    void midiDecrease();
    void midiIncrease();
    void midiDefault();
    void midiChangedInternal(byte layerNumber);

public:
    ENC(int a, int b, int button, uint16_t* specifier, byte midiControlNumberPrimary, byte midiControlNumberSecondary);

    void tick();

    void nothing();

    void upMidiLayer();
    void downMidiLayer();
    void midiChangedExternal(byte midiControlNumber, byte value);

    std::function<void()> click;
    std::function<void()> left;
    std::function<void()> right;
    std::function<void()> leftH;
    std::function<void()> rightH;
};

ENC::ENC(int a, int b, int button, uint16_t *specifier, byte midiControlNumberPrimary, byte midiControlNumberSecondary)
{
    this->encoder = EncButton(a, b, button, INPUT_PULLUP, INPUT_PULLUP);
    this->midiControlNumbers[0] = midiControlNumberPrimary;
    this->midiControlNumbers[1] = midiControlNumberSecondary;
    this->specifier = specifier;

    this->click = [&]
    {
        int type = this->specifier[0];
        uint16_t code = this->specifier[3];
        if (type == CONSUMER)
        {
            consumerKeyPress(code);
        }
        else if (type == NORMAL)
        {
            keyPress(code);
        }
        else if (type == MIDI)
        {
            midiDefault();
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
        else if (type == NORMAL)
        {
            keyPress(code);
        }
        else if (type == MIDI)
        {
            midiDecrease();
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
        else if (type == NORMAL)
        {
            keyPress(code);
        }
        else if (type == MIDI)
        {
            midiIncrease();
        }
    };
}

void ENC::tick()
{
    this->encoder.tick();

    if (this->encoder.click())
    {
        this->click();
        actionPerformed();
    }

    if (this->encoder.left())
    {
        this->left();
        actionPerformed();
    }

    if (this->encoder.leftH())
    {
        this->leftH();
        actionPerformed();
    }

    if (this->encoder.right())
    {
        this->right();
        actionPerformed();
    }

    if (this->encoder.rightH())
    {
        this->rightH();
        actionPerformed();
    }

    if (this->encoder.right())
    {
        this->right();
        actionPerformed();
    }

    if (this->encoder.hold())
    {
        this->reversed = !this->reversed;
        this->encoder.setEncReverse(reversed);
        Serial.print("reversed on ");
        Serial.println(midiControlNumbers[0]);
        actionPerformed();
    }
}

void ENC::upMidiLayer()
{
  midiLayer = 1;
  Serial.println("upMidiLayer");
}

void ENC::downMidiLayer()
{
  midiLayer = 0;
  Serial.println("downMidiLayer");
}

void ENC::midiDecrease()
{
  byte curVal = midiValues[midiLayer];
  if (curVal > 0) {
    curVal = curVal - 1;
  }
  midiValues[midiLayer] = curVal;
  midiChangedInternal(midiLayer);
}

void ENC::midiIncrease()
{
  byte curVal = midiValues[midiLayer];
  if (curVal < 127) {
    curVal = curVal + 1;
  }
  midiValues[midiLayer] = curVal;
  midiChangedInternal(midiLayer);
}

void ENC::midiDefault()
{
  midiValues[midiLayer] = 64;
  midiChangedInternal(midiLayer);
}

void ENC::midiChangedInternal(byte layerNumber) {
  byte midiValue = midiValues[layerNumber];
  byte midiControlNumber = midiControlNumbers[layerNumber];
  Serial.print("midi change on midiControlNumber ");
  Serial.print(midiControlNumber);
  Serial.print(" to value ");
  Serial.println(midiValue);

  sendControlMessage(1, midiControlNumber, midiValue);
}

void ENC::midiChangedExternal(byte midiControlNumber, byte value) {
  for (int i = 0; i < 2; i++) {
    if (midiControlNumbers[i] == midiControlNumber) {
      midiValues[i] = value;
      midiChangedInternal(i);
    }
  }
}

void ENC::nothing()
{
}

#endif