/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** core.c
*/

#include <string.h>
#include <stdio.h>
#include "chip8.h"

chip8_t *get_chip(void)
{
    static chip8_t chip;

    return &chip;
}

int initialize(const char *filepath)
{
    chip8_t *chip = get_chip();
    FILE *stream = NULL;

    if (filepath == NULL)
        return -1;

    stream = fopen(filepath, "rb");
    if (stream == NULL) {
        return -1;
    }

    memset(chip->memory, 0, MEM_SIZE);
    memset(chip->registers, 0, REG_NB);

    for (size_t i = MEM_START; i < CHAR_SIZE; ++i) {
        chip->memory[i] = font[i];
    }

    fread(&chip->memory[MEM_PROG], 1, MEM_SIZE - MEM_PROG, stream);

    chip->pc = MEM_PROG;
    return 0;
}

int exec_next_instruction(void)
{
    chip8_t *chip = get_chip();
    unsigned short opcode = GET_OPCODE(chip->memory, chip->pc);
    fptr func = get_function(opcode & 0xF000);

    if (func && func(opcode & 0x0FFF) == 0) {
        chip->pc += 2;
        return 0;
    }
    return -1;
}

int execution_loop(void)
{
    chip8_t *chip = get_chip();

    while (chip->pc < MEM_SIZE) {
        if (exec_next_instruction() < 0)
            return 84;
    }
    return 0;
}