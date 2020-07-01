/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** opcode.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chip8.h"

const fptr opcodes[NB_OPCODE] = {
        [0x0] = op_0XXX,
        [0x1] = op_1XXX,
        [0x2] = op_2XXX,
        [0x3] = op_3XXX,
        [0x4] = op_4XXX,
        [0x5] = op_5XXX,
        [0x6] = op_6XXX,
        [0x7] = op_7XXX,
        [0x8] = op_8XXX,
        [0x9] = op_9XXX,
        [0xA] = op_AXXX,
        [0xB] = op_BXXX,
        [0xC] = op_CXXX,
        [0xD] = op_DXXX,
        [0xE] = op_EXXX,
        [0xF] = op_FXXX
};

void op_0XXX(ushort args)
{
    chip8_t *chip = get_chip();

    if (args == 0x0E0) {
        memset(chip->graphics->frame_buffer, 0, CHIP_WIDTH * CHIP_HEIGHT);
        chip->graphics->render_flag = true;
    } else if (args == 0x0EE) {
        chip->sp--;
        chip->pc = chip->stack[chip->sp];
    }
    chip->pc += 2;
}

void op_1XXX(ushort op_7XXXr)
{
    chip8_t *chip = get_chip();

    chip->pc = op_7XXXr;
}

void op_2XXX(ushort op_7XXXr)
{
    chip8_t *chip = get_chip();

    chip->stack[chip->sp] = chip->pc;
    chip->sp++;
    chip->pc = op_7XXXr;
}

void op_3XXX(ushort args)
{
    chip8_t *chip = get_chip();

    if (chip->registers[(args & 0xF00u) >> 8u] == (args & 0x0FFu)) {
        chip->pc += 2;
    }
    chip->pc += 2;
}

void op_4XXX(ushort args)
{
    chip8_t *chip = get_chip();

    if (chip->registers[(args & 0xF00u) >> 8u] != (args & 0x0FFu)) {
        chip->pc += 2;
    }
    chip->pc += 2;
}

void op_5XXX(ushort args)
{
    chip8_t *chip = get_chip();

    if ((args & 0x00Fu) != 0)
        return;

    if (chip->registers[((args & 0xF00u) >> 8u)] == chip->registers[((args & 0x0F0u) >> 4u)]) {
        chip->pc += 2;
    }
    chip->pc += 2;
}

void op_6XXX(ushort args)
{
    chip8_t *chip = get_chip();

    chip->registers[(args & 0xF00u) >> 8u] = (args & 0x0FFu);
    chip->pc += 2;
}

void op_7XXX(ushort args)
{
    chip8_t *chip = get_chip();
    uchar index = (args & 0xF00u) >> 8u;

    chip->registers[index] += (args & 0x0FFu);
    chip->pc += 2;
}

void op_8XXX(ushort args)
{
    chip8_t *chip = get_chip();
    uchar *regX = &chip->registers[(args & 0xF00u) >> 8u];
    uchar *regY = &chip->registers[(args & 0x0F0u) >> 4u];

    switch (args & 0x00Fu) {
        case 0x0:
            // LD
            *regX = *regY;
            break;
        case 0x1:
            // OR
            *regX |= *regY;
            break;
        case 0x2:
            // AND
            *regX &= *regY;
            break;
        case 0x3:
            // XOR
            *regX ^= *regY;
            break;
        case 0x4:
            // ADD
            CARRY(chip) = (*regX + *regY > 0xff ? 0x1: 0x0);
            *regX = (*regX + *regY) % 0x100u;
            break;
        case 0x5:
            // SUB
            CARRY(chip) = (*regX > *regY ? 0x1 : 0x0);
            *regX -= *regY;
            break;
        case 0x6:
            // SHR
            CARRY(chip) = *regX & 0b00000001u;
            *regX = *regY >> 1u;
            break;
        case 0x7:
            // SUBN
            CARRY(chip) = (*regX > *regY ? 0x1 : 0x0);
            *regX = *regY - *regX;
            break;
        case 0xE:
            //SHL
            CARRY(chip) = (*regX & 0b10000000u ? 1 : 0);
            *regX = *regY << 1u;
            break;
    }
    chip->pc += 2;
}

void op_9XXX(ushort args)
{
    chip8_t *chip = get_chip();

    if (chip->registers[((args & 0xF00u) >> 8u)] != chip->registers[((args & 0x0F0u) >> 4u)]) {
        chip->pc += 2;
    }
    chip->pc += 2;
}

void op_AXXX(ushort args)
{
    chip8_t *chip = get_chip();

    chip->mem_op_addr_register = args;
    chip->pc += 2;
}

void op_BXXX(ushort args)
{
    chip8_t *chip = get_chip();

    chip->pc = chip->registers[0] + args;
}

void op_CXXX(ushort args)
{
    chip8_t *chip = get_chip();
    uchar random_nb = rand() % 0x100;

    chip->registers[((args & 0xF00u) >> 8u)] = (random_nb & (args & 0x0FFu));
    chip->pc += 2;
}

void op_DXXX(ushort args)
{
    chip8_t *chip = get_chip();
    uchar regX = chip->registers[(args & 0xF00u) >> 8u];
    uchar regY = chip->registers[(args & 0x0F0u) >> 4u];
    uchar start_op_7XXXr = chip->mem_op_addr_register;
    uchar n = args & 0x00Fu;

    CARRY(chip) = 0;
    for (uchar i = 0; i < n; ++i) {
        for (uchar mask = 0b10000000u, tmp = regX; mask > 0; mask >>= 1u, ++tmp) {
            if (chip->memory[i + start_op_7XXXr] & mask) {
                if (chip->graphics->frame_buffer[CHIP_WIDTH * (regY + i) + tmp])
                    CARRY(chip) = 1;
                chip->graphics->frame_buffer[CHIP_WIDTH * (regY + i) + tmp] ^= 1u;
                chip->graphics->render_flag = true;
            }
        }
    }
    chip->pc += 2;
}

void op_EXXX(ushort args)
{
    chip8_t *chip = get_chip();

    switch (args & 0x0FFu) {
        case 0x9E:
            if (is_op_EXXX(chip->registers[(args & 0xF00u) >> 8u]))
                chip->pc += 2;
            break;
        case 0xA1:
            if (!is_op_EXXX(chip->registers[(args & 0xF00u) >> 8u]))
                chip->pc += 2;
            break;
    }
    chip->pc += 2;
}

void op_FXXX(ushort args)
{
    chip8_t *chip = get_chip();
    uchar *regX = &chip->registers[(args & 0xF00u) >> 8u];

    switch (args & 0x0FFu) {
        case 0x07:
            *regX = chip->timers[DT];
            break;
        case 0x0A:
            *regX = wait_for_keypress();
            break;
        case 0x15:
            chip->timers[DT] = *regX;
            break;
        case 0x18:
            chip->timers[ST] = *regX;
            break;
        case 0x1E:
            chip->mem_op_addr_register += *regX;
            break;
        case 0x29:
            chip->mem_op_addr_register = *regX * FONT_SIZE;
            break;
        case 0x33:
            chip->memory[chip->mem_op_addr_register] = *regX % 10;
            chip->memory[chip->mem_op_addr_register + 1] = (*regX / 10) % 10;
            chip->memory[chip->mem_op_addr_register + 2] = (*regX / 100) % 10;
            break;
        case 0x55:
            for (uint i = 0; i < ((args & 0xF00u) >> 8u); ++i) {
                chip->memory[chip->mem_op_addr_register + i] = chip->registers[i];
            }
            chip->mem_op_addr_register += ((args & 0xF00u) >> 8u) + 1;
            break;
        case 0x65:
            for (uint i = 0; i < ((args & 0xF00u) >> 8u); ++i) {
                chip->registers[i] = chip->memory[chip->mem_op_addr_register + i];
            }
            chip->mem_op_addr_register += ((args & 0xF00u) >> 8u) + 1;
            break;
    }
    chip->pc += 2;
}
