/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** keyboard.h
*/

#ifndef CHIP_8_KEYBOARD_H
#define CHIP_8_KEYBOARD_H

#include "chip8.h"

SDL_Scancode get_scancode(uchar key);
bool is_op_EXXX(uchar key);
uchar wait_for_keypress(void);
void get_keys_states(void);

#endif //CHIP_8_KEYBOARD_H
