#include <stdint.h>
#include <Keyboard.h>

extern long lastKeyPressTimestamp;
extern double backlightBrightness;

void keyDown(uint8_t keycode);
void keyUp(uint8_t keycode);
void keyPress(uint8_t keycode);

void consumerKeyPress(uint16_t keycode);

#define O_KEY_PLAY_PAUSE KEY_PLAY_PAUSE
#define O_KEY_VOLUME_INCREMENT KEY_VOLUME_INCREMENT
#define O_KEY_VOLUME_DECREMENT KEY_VOLUME_DECREMENT

#define O_KEY_RETURN KEY_RETURN
#define O_KEY_UP_ARROW KEY_UP_ARROW
#define O_KEY_DOWN_ARROW KEY_DOWN_ARROW
#define O_KEY_LEFT_ARROW KEY_LEFT_ARROW
#define O_KEY_RIGHT_ARROW KEY_RIGHT_ARROW
#define O_KEY_F19 KEY_F19
#define O_KEY_F17 KEY_F17
#define O_KEY_F18 KEY_F18