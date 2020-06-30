/*
** EPITECH PROJECT, 2019
** CHIP-8
** File description:
** chip8.h
*/

#ifndef CHIP_8_CHIP8_H
#define CHIP_8_CHIP8_H

#include "font.h"
#include "opcode.h"
#include "graphics.h"
#include "types.h"
#include "keyboard.h"

#define MEM_SIZE        0xFFF
#define STACK_SIZE      12
#define REG_NB          16
#define KEY_NB          16
#define CARRY(chip)     (chip->registers[REG_NB - 1])

#define MEM_FONT        0x000
#define MEM_PROG        0x200

#define DT              0
#define ST              1

struct chip8_s {
    graphics_t *graphics;

    uchar memory[MEM_SIZE];
    uchar registers[REG_NB];
    uchar keys[KEY_NB];
    ushort stack[STACK_SIZE];

    ushort mem_addr_register;
    ushort pc;
    uchar sp;
    uchar timers[2];
};

typedef struct chip8_s chip8_t;

int init_chip(const char *filepath);
chip8_t *get_chip(void);
int exec_next_instruction(void);
int execution_loop(void);

#endif //CHIP_8_CHIP8_H