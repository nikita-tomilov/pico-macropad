#ifndef CKEYLAYERS_H
#define CKEYLAYERS_H

#include "keymap.h"
#define MAX_LAYERS 2
#define MAX_LAYER_INDEX (MAX_LAYERS-1)

// clang-format off
char keyLayer0[8] = { O_KEY_SHIFT, '2', '5', '6', 
                      '3', '4', '7', '8'};
char keyLayer1[8] = { O_KEY_SHIFT, 'b', 'c', 'd', 
                      'e', 'f', 'g', 'h'};
char* keyLayers[] = { keyLayer0, keyLayer1 };
// clang-format on

// clang-format off

uint16_t encLayer0[] = {
    CONSUMER, O_KEY_VOLUME_DECREMENT, O_KEY_VOLUME_INCREMENT, O_KEY_PLAY_PAUSE,
    NORMAL,   O_KEY_LEFT_ARROW,       O_KEY_RIGHT_ARROW,      O_KEY_SPACE,
    NORMAL,   O_KEY_DOWN_ARROW,       O_KEY_UP_ARROW,         O_KEY_RETURN,
    CONSUMER, O_KEY_BACK,             O_KEY_FWD,              O_KEY_REFRESH };
uint16_t encLayer1[] = {
    NORMAL, O_KEY_F13, O_KEY_F14, O_KEY_F15,
    NORMAL, O_KEY_F16, O_KEY_F17, O_KEY_F18,
    NORMAL, O_KEY_F19, O_KEY_F20, O_KEY_F21,
    NORMAL, O_KEY_F22, O_KEY_F23, O_KEY_F24, };
uint16_t* encLayers[] = { encLayer0, encLayer1 };
// clang-format on

#endif