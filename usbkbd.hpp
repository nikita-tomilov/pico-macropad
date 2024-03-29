#ifndef CUSBKBD_H
#define CUSBKBD_H

#include <Adafruit_TinyUSB.h>
#include <Arduino.h>

enum
{
  RID_KEYBOARD = 1,
  RID_MOUSE,
  RID_CONSUMER_CONTROL,
};

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
  TUD_HID_REPORT_DESC_MOUSE   ( HID_REPORT_ID(RID_MOUSE) ),
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
};

extern Adafruit_USBD_HID usb_hid;

#define CONSUMER  1
#define NORMAL    2
#define MIDI      3

void keyDown(uint8_t keycode);
void keyUp(uint8_t keycode);
void keyPress(uint8_t keycode);

void consumerKeyPress(uint16_t keycode);

#define O_KEY_PLAY_PAUSE HID_USAGE_CONSUMER_PLAY_PAUSE
#define O_KEY_VOLUME_INCREMENT HID_USAGE_CONSUMER_VOLUME_INCREMENT
#define O_KEY_VOLUME_DECREMENT HID_USAGE_CONSUMER_VOLUME_DECREMENT

#define O_KEY_BACK HID_USAGE_CONSUMER_AC_BACK
#define O_KEY_FWD HID_USAGE_CONSUMER_AC_FORWARD
#define O_KEY_REFRESH HID_USAGE_CONSUMER_AC_REFRESH

#define O_KEY_SHIFT HID_KEY_SHIFT_LEFT
#define O_KEY_RETURN HID_KEY_RETURN
#define O_KEY_SPACE HID_KEY_SPACE
#define O_KEY_UP_ARROW HID_KEY_ARROW_UP
#define O_KEY_DOWN_ARROW HID_KEY_ARROW_DOWN
#define O_KEY_LEFT_ARROW HID_KEY_ARROW_LEFT
#define O_KEY_RIGHT_ARROW HID_KEY_ARROW_RIGHT
#define O_KEY_DELETE HID_KEY_DELETE

#define O_KEY_R HID_KEY_R
#define O_KEY_W HID_KEY_W
#define O_KEY_5 HID_KEY_5
#define O_KEY_6 HID_KEY_6
#define O_KEY_0 HID_KEY_0

#define O_KEY_F13 HID_KEY_F13
#define O_KEY_F14 HID_KEY_F14
#define O_KEY_F15 HID_KEY_F15
#define O_KEY_F16 HID_KEY_BACKSPACE // windows 10
#define O_KEY_F17 HID_KEY_F17
#define O_KEY_F18 HID_KEY_F18
#define O_KEY_F19 HID_KEY_F19
#define O_KEY_F20 HID_KEY_F20
#define O_KEY_F21 HID_KEY_F21
#define O_KEY_F22 HID_KEY_F22
#define O_KEY_F23 HID_KEY_F23
#define O_KEY_F24 HID_KEY_F24


void keyPressDetected()
{
    if (!usb_hid.ready())
        return;

    if (TinyUSBDevice.suspended())
    {
        TinyUSBDevice.remoteWakeup();
    }
}

void keyDown(uint8_t keycode)
{
    keyPressDetected();

    uint8_t keycodes[6] = {HID_KEY_NONE};
    keycodes[0] = keycode;
    usb_hid.keyboardReport(RID_KEYBOARD, 0, keycodes);

    Serial.println(keycode);
}

void keyUp(uint8_t keycode)
{
    keyPressDetected();

    usb_hid.keyboardRelease(RID_KEYBOARD);
}

void keyPress(uint8_t keycode)
{
    keyDown(keycode);
    delay(15);
    keyUp(keycode);
}

void consumerKeyPress(uint16_t keycode)
{
    keyPressDetected();
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, keycode);
    delay(15);
    usb_hid.sendReport16(RID_CONSUMER_CONTROL, 0);
}


#endif