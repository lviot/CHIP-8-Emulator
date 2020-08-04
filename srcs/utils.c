/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** utils.c
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

unsigned int make_seed(void)
{
    unsigned int seed = 0;
    int fd = open("/dev/random", O_RDONLY);

    if (fd < 0 || read(fd, &seed, sizeof(seed)) < 0) {
        return 0;
    }
    close(fd);
    return seed;
}