/*
** EPITECH PROJECT, 2019
** CHIP-8
** File description:
** chip8.h
*/

#ifndef CHIP_8_CHIP8_H
#define CHIP_8_CHIP8_H

//#define _DEBUG

#include "font.h"
#include "opcode.h"
#include "graphics.h"
#include "audio.h"
#include "types.h"
#include "keyboard.h"

#define MEM_SIZE        0xFFF
#define STACK_SIZE      12
#define REG_NB          16
#define KEY_NB          16
#define CARRY(chip)     (chip->registers[REG_NB - 1])

#define MEM_FONT        0x000 // 0x050
#define MEM_PROG        0x200

#define DT              0
#define ST              1

struct chip8_s
{
    graphics_t *graphics;

    audio_t *audio;

    uchar memory[MEM_SIZE];
    uchar registers[REG_NB];
    uchar keys[KEY_NB];
    ushort stack[STACK_SIZE];

    ushort addr_register;
    ushort pc;
    uchar sp;
    uchar timers[2];
};

typedef struct chip8_s chip8_t;

struct exec_args_s
{
    char *filepath;
    ushort ratio;
};

typedef struct exec_args_s exec_args_t;

int init_chip(const char *);
chip8_t *get_chip(void);
void exec_next_instruction(void);
int execution_loop(void);

unsigned int make_seed(void);
exec_args_t *parse_cmdline_args(int argc, char *argv[]);

#endif //CHIP_8_CHIP8_H