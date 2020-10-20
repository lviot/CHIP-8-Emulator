/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** keypad.h
*/

#ifndef CHIP_8_FONT_H
#define CHIP_8_FONT_H

#include "types.h"

#define CHAR_NB     16
#define FONT_SIZE   5
#define CHAR_SIZE   CHAR_NB * FONT_SIZE

extern const uchar font_sprites[CHAR_SIZE];

#endif //CHIP_8_FONT_H
