#ifndef CLEDRING_H
#define CLEDRING_H

#define DATA_PIN 13
#define CIRCLE_BEGIN_OFFSET 4

void ledringSetup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  FastLED.setBrightness(10);
  leds[0] = CRGB::Pink;
  FastLED.show();
  delay(100);
  leds[1] = CRGB::Red;
  FastLED.show();
  delay(100);
  leds[2] = CRGB::Orange;
  FastLED.show();
  delay(100);
  leds[3] = CRGB::Yellow;
  FastLED.show();
  delay(100);
  leds[4] = CRGB::Green;
  FastLED.show();
  delay(100);
  leds[5] = CRGB::Cyan;
  FastLED.show();
  delay(100);
  leds[6] = CRGB::Blue;
  FastLED.show();
  delay(100);
  leds[7] = CRGB::Purple;
  FastLED.show();
  delay(100);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();

  FastLED.setBrightness(50);
}

void enableMidiMode() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(16, 16, 16);
  }
  FastLED.show();
}

void disableMidiMode() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void setLedValue(uint8_t idx, uint8_t r, uint8_t g, uint8_t b) {
  byte i = (idx + CIRCLE_BEGIN_OFFSET) % NUM_LEDS;
  leds[i] = CRGB(r, g, b);
}


void setMidiValue(byte value) {
  setLedValue(0, 64, 0, 0);

  byte step = 126 / (NUM_LEDS - 1);
  byte cnt = 0;

  for (int i = 1; i < NUM_LEDS; i++) {
    if ((cnt < value) && (cnt + step > value)) {
      byte diff = (value - cnt);
      byte maxVal = step * 2;
      byte minValOffset = 5;
      byte bright = (diff * maxVal) / step + minValOffset;

      Serial.print(diff);
      Serial.print("; ");
      Serial.print(step);
      Serial.print("; ");
      Serial.println(bright);

      setLedValue(i, bright, 0, 0);
    
    } else if (cnt < value) {
      setLedValue(i, step, step, step);
    } else if (cnt > value) {
      setLedValue(i, 0, 0, 0);
    }
    cnt += step;
  }
  FastLED.show();
}

#endif
