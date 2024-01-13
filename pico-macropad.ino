#include <Arduino.h>
#include <vector>
#include <FastLED.h>

#include "led.hpp"
LED red(5, 1023);
LED green(3, 768);
LED yellow(9, 1023);
LED blue(11, 768);
LED white(1, 1023);
std::vector<LED> allLeds = { red, green, yellow, blue, white };

#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
#include "ledring.h"

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
std::vector<ENC> allEncoders = {enc1, enc2, enc3, enc4};

// clang-format on

long lastKeyPressTimestamp = millis();
void actionPerformed() {
  lastKeyPressTimestamp = millis();
}

double backlightBrightness = 100.0;

int mode = 0;
bool modifierPressed = false;

void modifierKeyDown() {
  Serial.println("modifier down");
  modifierPressed = true;
  enc1.upMidiLayer();
  enc2.upMidiLayer();
  enc3.upMidiLayer();
  enc4.upMidiLayer();
}

void modifierKeyUp() {
  Serial.println("modifier up");
  modifierPressed = false;
  enc1.downMidiLayer();
  enc2.downMidiLayer();
  enc3.downMidiLayer();
  enc4.downMidiLayer();
}

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

  for (auto &it : allKeys) {
    if (it.isModifier() && (mode == 1)) {
      // Serial.println("Changed key to MIDI mode");
      it.keydown = [&]{ modifierKeyDown(); };
      it.keyup   = [&]{ modifierKeyUp();   };
    } else {
      // Serial.println("Changed key to NORMAL mode");
      it.keydown = it.defaultkeydown;
      it.keyup = it.defaultkeyup;
    }
  }

  if (mode == 1) {
    enableMidiMode();
  } else {
    disableMidiMode();
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

void controlMessageReceived(byte channel, byte controlNumber, byte value) {
  if (channel == 1) {
    enc1.midiChangedExternal(controlNumber, value);
    enc2.midiChangedExternal(controlNumber, value);
    enc3.midiChangedExternal(controlNumber, value);
    enc4.midiChangedExternal(controlNumber, value);
  }
}

void midiValueUpdated(byte controlNumber, byte value) {
  if (controlNumber == 31) {
    setMidiValue(value);
  }
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
  ledringSetup();
  // white.on();

  enc1.rightH = [&] {
    enc1rightH();
  };

  enc1.leftH = [&] {
    enc1leftH();
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
    if (!modifierPressed) {
      red.set(backlightBrightness);
      yellow.set(backlightBrightness);
      green.set(backlightBrightness);
      blue.set(backlightBrightness);
      white.set(0);
    } else {
      red.set(0);
      yellow.set(0);
      green.set(0);
      blue.set(0);
      white.set(backlightBrightness);
    }
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