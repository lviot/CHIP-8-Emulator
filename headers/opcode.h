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
#define GET_OPCODE(mem, pc) (((mem[pc]) << 8u) | (mem[pc + 1]))

typedef int (*fptr)(ushort);

struct opcode_map_s
{
    ushort value;
    fptr func;
};

typedef struct opcode_map_s opcode_map_t;

extern const opcode_map_t map[NB_OPCODE];

extern const fptr opcodes[NB_OPCODE];

fptr get_function(ushort value);

int chip_syscall(ushort);
int jump(ushort);
int call(ushort);
int skip_if_val_equal(ushort);
int skip_if_val_not_equal(ushort);
int skip_if_reg_equal(ushort);
int load_val(ushort);
int add(ushort);
int opcode_8(ushort);
int skip_if_reg_not_equal(ushort);
int load_in_i(ushort);
int jump_reg(ushort);
int gen_rand(ushort);
int draw(ushort);
int key_pressed(ushort);
int opcode_F(ushort);

#endif //CHIP_8_OPCODE_H
