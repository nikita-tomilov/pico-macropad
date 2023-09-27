#include <stdint.h>
#include <Keyboard.h>

#define CONSUMER  1
#define NORMAL    2

extern long lastKeyPressTimestamp;
extern double backlightBrightness;

void keyDown(uint8_t keycode);
void keyUp(uint8_t keycode);
void keyPress(uint8_t keycode);

void consumerKeyPress(uint16_t keycode);

#define O_KEY_PLAY_PAUSE KEY_PLAY_PAUSE
#define O_KEY_VOLUME_INCREMENT KEY_VOLUME_INCREMENT
#define O_KEY_VOLUME_DECREMENT KEY_VOLUME_DECREMENT

#define O_KEY_BACK KEY_AC_BACK
#define O_KEY_FWD KEY_AC_FORWARD
#define O_KEY_REFRESH KEY_AC_REFRESH

#define O_KEY_SHIFT KEY_LEFT_SHIFT
#define O_KEY_RETURN KEY_RETURN
#define O_KEY_SPACE ' '
#define O_KEY_UP_ARROW KEY_UP_ARROW
#define O_KEY_DOWN_ARROW KEY_DOWN_ARROW
#define O_KEY_LEFT_ARROW KEY_LEFT_ARROW
#define O_KEY_RIGHT_ARROW KEY_RIGHT_ARROW

#define O_KEY_F13 KEY_F13
#define O_KEY_F14 KEY_F14
#define O_KEY_F15 KEY_F15
#define O_KEY_F16 KEY_KP_DOT // windows 10
#define O_KEY_F17 KEY_F17
#define O_KEY_F18 KEY_F18
#define O_KEY_F19 KEY_F19
#define O_KEY_F20 KEY_F20
#define O_KEY_F21 KEY_F21
#define O_KEY_F22 KEY_F22
#define O_KEY_F23 KEY_F23
#define O_KEY_F24 KEY_F24