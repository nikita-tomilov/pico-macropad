#include <Arduino.h>
#include <vector>

#include "led.hpp"
LED red(5, 1023);
LED green(3, 768);
LED yellow(9, 1023);
LED blue(11, 768);
LED white(1, 1023);
std::vector<LED> allLeds = { red, green, yellow, blue, white };

#include "usbkbd.hpp"
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);
#include "usbmidi.hpp"
Adafruit_USBD_MIDI usb_midi;

#include "key.hpp"
#include "keylayers.h"
#include "enc.hpp"

// clang-format off
char cMap[8] = { '1', '2', '5', '6', 
                 '3', '4', '7', '8'};
KEY k1(4, &(cMap[0]));  KEY k2(2, &(cMap[1]));  KEY k5(0, &(cMap[2]));  KEY k6(6, &(cMap[3]));
KEY k3(10, &(cMap[4])); KEY k4(8, &(cMap[5]));  KEY k7(12, &(cMap[6])); KEY k8(7, &(cMap[7]));
std::vector<KEY> allKeys = {k1, k2, k3, k4, k5, k6, k7, k8};

// A, B, button
uint16_t encLayer[16];
ENC enc1(26, 27, 28, &(encLayer[0]), 31, 35);
ENC enc2(20, 21, 22, &(encLayer[4]), 32, 36);
ENC enc3(18, 17, 19, &(encLayer[8]), 33, 37);
ENC enc4(15, 14, 16, &(encLayer[12]),34, 38);

// clang-format on

long lastKeyPressTimestamp = millis();
double backlightBrightness = 100.0;

int mode = 0;

void changeMode(int newMode) {
  mode = newMode;
  Serial.print("Mode changed to ");
  Serial.println(mode);

  auto kl = keyLayers[mode];
  for (int i = 0; i < 8; i++) {
    cMap[i] = kl[i];
  }

  auto el = encLayers[mode];
  for (int i = 0; i < 16; i++) {
    encLayer[i] = el[i];
  }
}

void enc1leftH() {
  int newMode = mode - 1;
  if (newMode < 0) {
    newMode = 0;
  }
  changeMode(newMode);
}

void enc1rightH() {
  int newMode = mode + 1;
  if (newMode > MAX_LAYER_INDEX) {
    newMode = MAX_LAYER_INDEX;
  }
  changeMode(newMode);
}


volatile byte midiVal = 64;
void changeMidiVal(byte newVal) {
  midiVal = newVal;
  sendControlMessage(1, 31, midiVal);
}
void controlMessageReceived(byte channel, byte controlNumber, byte value) {
  Serial.print("> ");
  Serial.print(channel);
  Serial.print(" ");
  Serial.print(controlNumber);
  Serial.print(" ");
  Serial.print(value);
  Serial.println();
  if (channel == 1) {
    if (controlNumber == 31) {
      if (midiVal != value) {
       changeMidiVal(value);
      }
    }
  }
}
void enc2leftH() {
  if (midiVal > 0) midiVal = midiVal - 1;
  changeMidiVal(midiVal);
}

void enc2rightH() {
  if (midiVal < 127) midiVal = midiVal + 1;
  changeMidiVal(midiVal);
}

void usbSetup() {
  usb_hid.begin();
  usb_midi.begin();
  Serial.begin(115200);
  while (!TinyUSBDevice.mounted()) {
    delay(1);
  }
}

void setup(void) {
  usbSetup();
  changeMode(0);

  analogWriteFreq(1000);
  analogWriteRange(1024);

  // white.on();

  enc1.rightH = [&] {
    enc1rightH();
  };

  enc1.leftH = [&] {
    enc1leftH();
  };
  enc2.rightH = [&] {
    enc2rightH();
  };

  enc2.leftH = [&] {
    enc2leftH();
  };
}

void ledRoutine() {
  if (millis() - lastKeyPressTimestamp < 10000) {
    backlightBrightness = 100;
  } else {
    if (backlightBrightness > 0) {
      backlightBrightness -= 0.1;
    }
  }
  if (mode == 0) {
    for (auto &it : allLeds) {
      it.set(backlightBrightness);
    }
  } else if (mode == 1) {
    red.set(0);
    yellow.set(0);
    green.set(0);
    blue.set(0);
    white.set(backlightBrightness);
  } else if (mode == 2) {
    red.set(backlightBrightness);
    yellow.set(backlightBrightness);
    green.set(backlightBrightness);
    blue.set(backlightBrightness);
    white.set(0);
  }
}


void loop() {
  ledRoutine();
  midiRoutine();

  enc1.tick();
  enc2.tick();
  enc3.tick();
  enc4.tick();

  for (auto &it : allKeys) {
    it.tick();
  }

  delay(1);
}