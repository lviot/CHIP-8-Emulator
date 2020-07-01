/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** opcode.h
*/

#ifndef CHIP_8_OPCODE_H
#define CHIP_8_OPCODE_H

#include "types.h"

#define NB_OPCODE           35
#define GET_OPCODE(chip)    \
    (((chip->memory[chip->pc]) << 8u) | (chip->memory[chip->pc + 1]))

typedef void (*fptr)(ushort);

extern const fptr opcodes[NB_OPCODE];

void op_0XXX(ushort);
void op_1XXX(ushort);
void op_2XXX(ushort);
void op_3XXX(ushort);
void op_4XXX(ushort);
void op_5XXX(ushort);
void op_6XXX(ushort);
void op_7XXX(ushort);
void op_8XXX(ushort);
void op_9XXX(ushort);
void op_AXXX(ushort);
void op_BXXX(ushort);
void op_CXXX(ushort);
void op_DXXX(ushort);
void op_EXXX(ushort);
void op_FXXX(ushort);

#endif //CHIP_8_OPCODE_H
