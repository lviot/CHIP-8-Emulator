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
    if (initialize(argv[1])) {
        fprintf(stderr, "Cannot access requested file.\n");
        return 84;
    }
    return execution_loop();
}