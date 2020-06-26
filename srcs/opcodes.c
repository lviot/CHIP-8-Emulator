/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** opcode.c
*/

#include <stddef.h>
#include "opcode.h"

const opcode_map_t map[NB_OPCODE] = {
        {0x0000, opcode_0},
        {0x1000, opcode_1},
        {0x2000, opcode_2},
        {0x3000, opcode_3},
        {0x4000, opcode_4},
        {0x5000, opcode_5},
        {0x6000, opcode_6},
        {0x7000, opcode_7},
        {0x8000, opcode_8},
        {0x9000, opcode_9},
        {0xA000, opcode_A},
        {0xB000, opcode_B},
        {0xC000, opcode_C},
        {0xD000, opcode_D},
        {0xE000, opcode_E},
        {0xF000, opcode_F}
};

fptr get_function(unsigned short value)
{
    for (size_t i = 0; i < NB_OPCODE; ++i) {
        if (map[i].value == value) {
            return map[i].func;
        }
    }
    return NULL;
}

int opcode_0(unsigned short args)
{
    return 0;
}

int opcode_1(unsigned short args)
{
    return 0;
}

int opcode_2(unsigned short args)
{
    return 0;
}

int opcode_3(unsigned short args)
{
    return 0;
}

int opcode_4(unsigned short args)
{
    return 0;
}

int opcode_5(unsigned short args)
{
    return 0;
}

int opcode_6(unsigned short args)
{
    return 0;
}

int opcode_7(unsigned short args)
{
    return 0;
}

int opcode_8(unsigned short args)
{
    return 0;
}

int opcode_9(unsigned short args)
{
    return 0;
}

int opcode_A(unsigned short args)
{
    return 0;
}

int opcode_B(unsigned short args)
{
    return 0;
}

int opcode_C(unsigned short args)
{
    return 0;
}

int opcode_D(unsigned short args)
{
    return 0;
}

int opcode_E(unsigned short args)
{
    return 0;
}

int opcode_F(unsigned short args)
{
    return 0;
}
