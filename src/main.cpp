#include <Arduino.h>

#include <vector>

#include <EncButton2.h>
#include "enc.h"
ENC enc1(26, 27, 28); // A, B, button
ENC enc2(20, 21, 22);
ENC enc3(18, 17, 19);
ENC enc4(15, 14, 16);

#include "led.h"
LED red(5, 1023);
LED green(3, 768);
LED yellow(9, 1023);
LED blue(11, 768);
LED white(1, 1023);

#include "keymap.h"

long lastKeyPressTimestamp = millis();
double backlightBrightness = 100.0;

void enc1click()
{
  Serial.println("Press 1");
  consumerKeyPress(O_KEY_PLAY_PAUSE);
}

void enc1left()
{
  Serial.println("Left 1 ");
  consumerKeyPress(O_KEY_VOLUME_DECREMENT);
}

void enc1right()
{
  Serial.println("Right 1");
  consumerKeyPress(O_KEY_VOLUME_INCREMENT);
}

void enc1leftH()
{
  /*mode -= 1;
  if (mode < 0)
  {
    mode = 0;
  }
  Serial.println(mode);*/
}

void enc1rightH()
{
  /*mode += 1;
  if (mode > 4)
  {
    mode = 4;
  }
  Serial.println(mode);*/
}

void enc2click()
{
  Serial.println("Press 2");
  keyPress(O_KEY_RETURN);
}

void enc2left()
{
  Serial.println("Left 2 ");
  keyPress(O_KEY_UP_ARROW);
}

void enc2right()
{
  Serial.println("Right 2");
  keyPress(O_KEY_DOWN_ARROW);
}

void enc3click()
{
  Serial.println("Press 3");
  keyPress(O_KEY_F19);
}

void enc3left()
{
  Serial.println("Left 3 ");
  keyPress(O_KEY_F17);
}

void enc3right()
{
  Serial.println("Right 3");
  keyPress(O_KEY_F18);
}

void setup(void)
{
  Serial.begin(115200);

  analogWriteFreq(1000);
  analogWriteRange(1024);

  white.on();

  enc1.click = [&]
  { enc1click(); };

  enc1.left = [&]
  { enc1left(); };

  enc1.leftH = [&]
  { enc1leftH(); };

  enc1.right = [&]
  { enc1right(); };

  enc1.rightH = [&]
  { enc1rightH(); };

  enc2.click = [&]
  { enc2click(); };

  enc2.left = [&]
  { enc2left(); };

  enc2.right = [&]
  { enc2right(); };

  enc3.click = [&]
  { enc3click(); };

  enc3.left = [&]
  { enc3left(); };

  enc3.right = [&]
  { enc3right(); };

  enc4.click = [&]
  { enc1click(); };

  enc4.left = [&]
  { enc1left(); };

  enc4.right = [&]
  { enc1right(); };

  delay(2000);
}

void loop()
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

  enc1.tick();
  enc2.tick();
  enc3.tick();
  enc4.tick();

  delay(2);
}