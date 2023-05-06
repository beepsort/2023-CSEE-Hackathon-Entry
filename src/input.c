#include "input.h"

uint8_t joypad_edge()
{
    static uint8_t cur_joypad = 0;
    static uint8_t last_joypad;
    last_joypad = cur_joypad;
    cur_joypad = joypad();
    uint8_t new_joypad = (cur_joypad ^ last_joypad) & cur_joypad;
    return new_joypad;
}
