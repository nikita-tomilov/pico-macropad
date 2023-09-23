#include <Arduino.h>
#include <vector>

#include "enc.h"
#include "keymap.h"
// A, B, button
ENC enc1(26, 27, 28, CONSUMER, O_KEY_VOLUME_DECREMENT, O_KEY_VOLUME_INCREMENT, O_KEY_PLAY_PAUSE);
ENC enc2(20, 21, 22, NORMAL, O_KEY_LEFT_ARROW, O_KEY_RIGHT_ARROW, O_KEY_RETURN);
ENC enc3(18, 17, 19, NORMAL, ',', '.', O_KEY_RETURN);
ENC enc4(15, 14, 16, NORMAL, '-', '+', O_KEY_RETURN);

#include "led.h"
LED red(5, 1023);
LED green(3, 768);
LED yellow(9, 1023);
LED blue(11, 768);
LED white(1, 1023);
std::vector<LED> allLeds = {red, green, yellow, blue, white};

#include "key.h"
#include "keylayers.h"
// clang-format off
char cMap[8] = { '1', '2', '5', '6', 
                 '3', '4', '7', '8'};
KEY k1(4, &(cMap[0]));  KEY k2(2, &(cMap[1]));  KEY k5(0, &(cMap[2]));  KEY k6(6, &(cMap[3]));
KEY k3(10, &(cMap[4])); KEY k4(8, &(cMap[5]));  KEY k7(12, &(cMap[6])); KEY k8(7, &(cMap[7]));
std::vector<KEY> allKeys = {k1, k2, k3, k4, k5, k6, k7, k8};
// clang-format on

long lastKeyPressTimestamp = millis();
double backlightBrightness = 100.0;

int mode = 0;
const int maxMode = 2;

void changeMode(int newMode)
{
  mode = newMode;
  Serial.print("Mode changed to ");
  Serial.println(mode);

  auto layer = keyLayers[mode];
  for (int i = 0; i < 8; i++)
  {
    cMap[i] = layer[i];
  }
}

void enc1leftH()
{
  int newMode = mode - 1;
  if (newMode < 0)
  {
    newMode = 0;
  }
  changeMode(newMode);
}

void enc1rightH()
{
  int newMode = mode + 1;
  if (newMode > maxMode)
  {
    newMode = maxMode;
  }
  changeMode(newMode);
}

void setup(void)
{
  Serial.begin(115200);

  analogWriteFreq(1000);
  analogWriteRange(1024);

  // white.on();

  enc1.rightH = [&]
  { enc1rightH(); };

  enc1.leftH = [&]
  { enc1leftH(); };

  mode = 0;
}

void ledRoutine()
{
  if (millis() - lastKeyPressTimestamp < 10000)
  {
    backlightBrightness = 100;
  }
  else
  {
    if (backlightBrightness > 0)
    {
      backlightBrightness -= 0.1;
    }
  }
  if (mode == 0)
  {
    for (auto &it : allLeds)
    {
      it.set(backlightBrightness);
    }
  }
  else if (mode == 1)
  {
    red.set(0);
    yellow.set(0);
    green.set(0);
    blue.set(0);
    white.set(backlightBrightness);
  }
  else if (mode == 2)
  {
    red.set(backlightBrightness);
    yellow.set(backlightBrightness);
    green.set(backlightBrightness);
    blue.set(backlightBrightness);
    white.set(0);
  }
}

void loop()
{
  ledRoutine();

  enc1.tick();
  enc2.tick();
  enc3.tick();
  enc4.tick();

  for (auto &it : allKeys)
  {
    it.tick();
  }

  delay(1);
}