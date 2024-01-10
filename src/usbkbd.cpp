#include "usbkbd.h"

void keyPressDetected()
{
    lastKeyPressTimestamp = millis();

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
