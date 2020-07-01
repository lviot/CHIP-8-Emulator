/*
** EPITECH PROJECT, 2019
** CHIP-8
** File description:
** main.c
*/

#include <stdio.h>
#include "chip8.h"

int main(int argc, char *argv[])
{
    if (argc != 2 || init_chip(argv[1])) {
        fprintf(stderr, "Cannot access requested file.\n");
        return 84;
    }
    if (execution_loop()) {
        return 84;
    }
    destroy_graphics();
    return 0;
}