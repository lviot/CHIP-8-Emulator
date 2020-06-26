/*
** EPITECH PROJECT, 2019
** CHIP-8
** File description:
** chip8.h
*/

#ifndef CHIP_8_CHIP8_H
#define CHIP_8_CHIP8_H

#include "opcode.h"
#include "font.h"

#define MEM_SIZE        0xFFF
#define REG_NB          16

#define MEM_START       0x000
#define MEM_PROG        0x200
#define MEM_ETI660      0x600

struct chip8_s {
    unsigned char memory[MEM_SIZE];
    unsigned char registers[REG_NB];
    unsigned short pc;
};

typedef struct chip8_s chip8_t;

int initialize(const char *filepath);
chip8_t *get_chip(void);
int exec_next_instruction(void);
int execution_loop(void);

#endif //CHIP_8_CHIP8_H