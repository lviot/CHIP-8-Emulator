/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** core.c
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.h"

const uchar font_sprites[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, //0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

chip8_t *get_chip(void)
{
    static chip8_t chip;

    return &chip;
}

int init_chip(const char *filepath)
{
    chip8_t *chip = get_chip();
    FILE *stream = NULL;

    srand(time(NULL));

    chip->graphics = init_graphics(WIN_WIDTH, WIN_HEIGHT);
    if (chip->graphics == NULL || filepath == NULL) {
        return -1;
    }

    stream = fopen(filepath, "rb");
    if (stream == NULL) {
        return -1;
    }

    memset(chip->memory, 0, MEM_SIZE);
    memset(chip->registers, 0, REG_NB);
    memset(chip->stack, 0, STACK_SIZE);
    memset(chip->keys, 0, KEY_NB);
    memset(chip->timers, 0, 2);

    for (uint i = 0; i < CHAR_SIZE; ++i) {
        chip->memory[MEM_FONT + i] = font_sprites[i];
    }

    fread(&chip->memory[MEM_PROG], 1, MEM_SIZE - MEM_PROG, stream);

    chip->pc = MEM_PROG;
    chip->sp = 0;
    chip->mem_op_addr_register = 0;
    return fclose(stream);
}

void exec_next_instruction(void)
{
    ushort opcode = GET_OPCODE(get_chip());

    opcodes[(opcode & 0xF000u) >> 12u](opcode & 0x0FFFu);
}

void decrease_timers(void)
{
    chip8_t *chip = get_chip();

    if (chip->timers[DT] > 0)
        chip->timers[DT]--;
    if (chip->timers[ST] > 0)
        chip->timers[ST]--;
}

int execution_loop(void)
{
    while (!catch_quit_event()) {
        exec_next_instruction();
        if (get_chip()->graphics->render_flag) {
            clear_screen();
            render();
            get_chip()->graphics->render_flag = false;
        }
        get_keys_states();
        decrease_timers();
        usleep(1200);
    }
    return 0;
}
