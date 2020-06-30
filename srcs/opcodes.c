/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** opcode.c
*/

#include <stdlib.h>
#include "chip8.h"

const opcode_map_t map[NB_OPCODE] = {
        {0x0000, chip_syscall},
        {0x1000, jump},
        {0x2000, call},
        {0x3000, skip_if_val_equal},
        {0x4000, skip_if_val_not_equal},
        {0x5000, skip_if_reg_equal},
        {0x6000, load_val},
        {0x7000, add},
        {0x8000, opcode_8},
        {0x9000, skip_if_reg_not_equal},
        {0xA000, load_in_i},
        {0xB000, jump_reg},
        {0xC000, gen_rand},
        {0xD000, draw},
        {0xE000, key_pressed},
        {0xF000, opcode_F}
};

fptr get_function(ushort value)
{
    for (size_t i = 0; i < NB_OPCODE; ++i) {
        if (map[i].value == value) {
            return map[i].func;
        }
    }
    return NULL;
}

int chip_syscall(ushort args)
{
    chip8_t *chip = get_chip();

    if (args == 0x0E0) {
        //clear_screen();
    } else if (args == 0x0EE) {
        chip->sp--;
        chip->pc = chip->stack[chip->sp];
    }
    chip->pc += 2;
    return 0;
}

int jump(ushort addr)
{
    chip8_t *chip = get_chip();

    chip->pc = addr;
    return 0;
}

int call(ushort addr)
{
    chip8_t *chip = get_chip();

    chip->stack[chip->sp] = chip->pc;
    chip->sp++;
    chip->pc = addr;
    return 0;
}

int skip_if_val_equal(ushort args)
{
    chip8_t *chip = get_chip();

    if (chip->registers[(args & 0xF00u) >> 8u] == (args & 0x0FFu)) {
        chip->pc += 2;
    }
    chip->pc += 2;
    return 0;
}

int skip_if_val_not_equal(ushort args)
{
    chip8_t *chip = get_chip();

    if (chip->registers[(args & 0xF00u) >> 8u] != (args & 0x0FFu)) {
        chip->pc += 2;
    }
    chip->pc += 2;
    return 0;
}

int skip_if_reg_equal(ushort args)
{
    chip8_t *chip = get_chip();

    if ((args & 0x00Fu) != 0)
        return 0;

    if (chip->registers[((args & 0xF00u) >> 8u)] == chip->registers[((args & 0x0F0u) >> 4u)]) {
        chip->pc += 2;
    }
    chip->pc += 2;
    return 0;
}

int load_val(ushort args)
{
    chip8_t *chip = get_chip();

    chip->registers[(args & 0xF00u) >> 8u] = (args & 0x0FFu);
    chip->pc += 2;
    return 0;
}

int add(ushort args)
{
    chip8_t *chip = get_chip();
    uchar index = (args & 0xF00u) >> 8u;

    chip->registers[index] += (args & 0x0FFu);
    chip->pc += 2;
    return 0;
}

int opcode_8(ushort args)
{
    chip8_t *chip = get_chip();
    uchar *regX = &chip->registers[(args & 0xF00u) >> 8u];
    uchar *regY = &chip->registers[(args & 0x0F0u) >> 4u];

    CARRY(chip) = 0;
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
            CARRY(chip) = (*regX + *regY > 0x100 ? 0x1: 0x0);
            *regX += *regY;
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
            CARRY(chip) = (*regY > *regX ? 0x1 : 0x0);
            *regX = *regY - *regX;
            break;
        case 0xE:
            //SHL
            CARRY(chip) = *regX & 0b00000001u;
            *regX = *regY << 1u;
            break;
    }
    chip->pc += 2;
    return 0;
}

int skip_if_reg_not_equal(ushort args)
{
    chip8_t *chip = get_chip();

    if ((args & 0x00Fu) != 0)
        return 0;

    if (chip->registers[((args & 0xF00u) >> 8u)] != chip->registers[((args & 0x0F0u) >> 4u)]) {
        chip->pc += 2;
    }
    chip->pc += 2;
    return 0;
}

int load_in_i(ushort args)
{
    chip8_t *chip = get_chip();

    chip->mem_addr_register = args;
    chip->pc += 2;
    return 0;
}

int jump_reg(ushort args)
{
    printf("jump reg\n");
    chip8_t *chip = get_chip();

    chip->pc = chip->registers[0] + args;
    return 0;
}

int gen_rand(ushort args)
{
    chip8_t *chip = get_chip();
    uchar random_nb = rand() % 0xFE;

    chip->registers[((args & 0xF00u) >> 8u)] = (random_nb & (args & 0x0FFu));
    chip->pc += 2;
    return 0;
}

int draw(ushort args)
{
    chip8_t *chip = get_chip();
    uchar regX = chip->registers[(args & 0xF00u) >> 8u];
    uchar regY = chip->registers[(args & 0x0F0u) >> 4u];
    uchar start_addr = chip->mem_addr_register;
    uchar n = args & 0x00Fu;

    CARRY(chip) = 0;
    for (uchar i = 0; i < n; ++i) {
        for (uchar mask = 0b10000000u, tmp = regX; mask > 0; mask >>= 1u, ++tmp) {
            if (chip->memory[MEM_FONT + i + start_addr] & mask) {
                if (chip->graphics->frame_buffer[CHIP_WIDTH * (regY + i) + tmp])
                    CARRY(chip) = 1;
                chip->graphics->frame_buffer[CHIP_WIDTH * (regY + i) + tmp] ^= 1u;
                chip->graphics->render_flag = true;
            }
        }
    }
    chip->pc += 2;
    return 0;
}

int key_pressed(ushort args)
{
    chip8_t *chip = get_chip();

    switch (args & 0x0FFu) {
        case 0x9E:
            if (is_key_pressed(chip->registers[(args & 0xF00u) >> 8u]))
                chip->pc += 2;
            break;
        case 0xA1:
            if (!is_key_pressed(chip->registers[(args & 0xF00u) >> 8u]))
                chip->pc += 2;
            break;
    }
    chip->pc += 2;
    return 0;
}

int opcode_F(ushort args)
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
            chip->mem_addr_register += *regX;
            break;
        case 0x29:
            chip->mem_addr_register = MEM_FONT + *regX * FONT_SIZE;
            break;
        case 0x33:
            chip->memory[chip->mem_addr_register] = *regX % 10;
            chip->memory[chip->mem_addr_register + 1] = (*regX / 10) % 10;
            chip->memory[chip->mem_addr_register + 2] = (*regX / 100) % 10;
            break;
        case 0x55:
            for (uint i = 0; i < ((args & 0xF00u) >> 8u); ++i) {
                chip->memory[chip->mem_addr_register + i] = chip->registers[i];
            }
            chip->mem_addr_register += ((args & 0xF00u) >> 8u) + 1;
            break;
        case 0x65:
            for (uint i = 0; i < ((args & 0xF00u) >> 8u); ++i) {
                chip->registers[i] = chip->memory[chip->mem_addr_register + i];
            }
            chip->mem_addr_register += ((args & 0xF00u) >> 8u) + 1;
            break;
    }
    chip->pc += 2;
    return 0;
}
