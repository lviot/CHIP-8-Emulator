/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** opcode.h
*/

#ifndef CHIP_8_OPCODE_H
#define CHIP_8_OPCODE_H

#define NB_OPCODE           35
#define GET_OPCODE(mem, pc) (mem[pc] << 8 | mem[pc + 1])

typedef int (*fptr)(unsigned short);

struct opcode_map_s
{
    unsigned short value;
    fptr func;
};

typedef struct opcode_map_s opcode_map_t;

extern const opcode_map_t map[NB_OPCODE];

extern const fptr opcodes[NB_OPCODE];

fptr get_function(unsigned short value);

int opcode_0(unsigned short);
int opcode_1(unsigned short);
int opcode_2(unsigned short);
int opcode_3(unsigned short);
int opcode_4(unsigned short);
int opcode_5(unsigned short);
int opcode_6(unsigned short);
int opcode_7(unsigned short);
int opcode_8(unsigned short);
int opcode_9(unsigned short);
int opcode_A(unsigned short);
int opcode_B(unsigned short);
int opcode_C(unsigned short);
int opcode_D(unsigned short);
int opcode_E(unsigned short);
int opcode_F(unsigned short);

#endif //CHIP_8_OPCODE_H
