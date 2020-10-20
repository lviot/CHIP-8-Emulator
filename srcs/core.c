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
#include "chip8.h"
#include "logger.h"

const uchar font_sprites[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
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

int init_chip(exec_args_t *args)
{
    chip8_t *chip = get_chip();
    FILE *stream = NULL;

    srand(make_seed());

    chip->graphics = init_graphics(WIN_WIDTH, WIN_HEIGHT);
    if (chip->graphics == NULL) {
        log_message(FATAL, "graphic module initialization failed");
        return -1;
    }

    chip->audio = init_audio();
    if (chip->audio == NULL) {
        log_message(FATAL, "audio module initialization failed");
        return -1;
    }

    stream = fopen(args->filepath, "rb");
    if (stream == NULL) {
        log_message(FATAL, "Cannot access requested file");
        return -1;
    }

    memset(chip->memory, 0, MEM_SIZE);
    memset(chip->registers, 0, REG_NB);
    memset(chip->stack, 0, STACK_SIZE);
    memset(chip->keys, 0, KEY_NB);
    memset(chip->timers, 0, 2);

    memcpy(&chip->memory[MEM_FONT], font_sprites, CHAR_SIZE);

    fread(&chip->memory[MEM_PROG], 1, MEM_SIZE - MEM_PROG, stream);

    chip->pc = MEM_PROG;
    chip->sp = 0;
    chip->addr_register = 0;

    free(args->filepath);
    free(args);
    return fclose(stream);
}

void exec_next_instruction(void)
{
    ushort opcode = GET_OPCODE(get_chip());

    log_message(INFO, "opcode: %x", opcode);
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
    // TODO: Sound implementation
    //setAudioStatus(true);
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
    destroy_graphics();
    return 0;
}
