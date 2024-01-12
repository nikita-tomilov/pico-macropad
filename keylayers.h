#ifndef CKEYLAYERS_H
#define CKEYLAYERS_H

#include "usbkbd.hpp"

#define MAX_LAYERS 2
#define MAX_LAYER_INDEX (MAX_LAYERS-1)

#define MAX_MIDI_LAYERS 2

// clang-format off
char keyLayer0[8] = { O_KEY_SHIFT, O_KEY_F13, O_KEY_F14, O_KEY_F15, 
                      O_KEY_F17,   O_KEY_F18, O_KEY_F19, O_KEY_F20};
char keyLayer1[8] = { O_KEY_R,          O_KEY_W,           O_KEY_5,     O_KEY_6, 
                      O_KEY_LEFT_ARROW, O_KEY_RIGHT_ARROW, 0x00,        O_KEY_0};
char* keyLayers[] = { keyLayer0, keyLayer1 };
// clang-format on

// clang-format off

uint16_t encLayer0[] = {
    CONSUMER, O_KEY_VOLUME_DECREMENT, O_KEY_VOLUME_INCREMENT, O_KEY_PLAY_PAUSE,
    NORMAL,   O_KEY_LEFT_ARROW,       O_KEY_RIGHT_ARROW,      O_KEY_SPACE,
    NORMAL,   O_KEY_DOWN_ARROW,       O_KEY_UP_ARROW,         O_KEY_RETURN,
    CONSUMER, O_KEY_BACK,             O_KEY_FWD,              O_KEY_REFRESH };
uint16_t encLayer1[] = {
    MIDI, 0, 0, 0,
    MIDI, 0, 0, 0,
    MIDI, 0, 0, 0,
    MIDI, 0, 0, 0, };
uint16_t* encLayers[] = { encLayer0, encLayer1 };
// clang-format on

#endif