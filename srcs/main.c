/*
** EPITECH PROJECT, 2019
** CHIP-8
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"
#include "logger.h"

void clean_exit(void)
{
    chip8_t *chip = get_chip();

    if (chip->graphics)
        free(chip->graphics);
    if (chip->audio)
        free(chip->audio);

    log_message(INFO, "Program stopped");
}

int main(int argc, char *argv[])
{
    atexit(clean_exit);
    exec_args_t *args = parse_cmdline_args(argc, argv);

    if (!args || init_chip(args)) {
        return 84;
    }
    if (execution_loop()) {
        return 84;
    }
    return 0;
}