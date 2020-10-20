/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** utils.c
*/

#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <limits.h>
#include "chip8.h"
#include "logger.h"

void display_help(void)
{
    printf("USAGE:\n");
    printf("\t./CHIP-8 -f <path_to_rom> [options]\n");
    printf("\n");
    printf("ARGUMENTS:\n");
    printf("\t-f, --file (required): path to rom\n");
    printf("\t-r, --ratio: pixel size ratio\n");
}

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

bool is_valid_number(const char *str)
{
    size_t index = 0;

    while (str[index]) {
        if (!isdigit(str[index]))
            return false;
        ++index;
    }
    return strcmp(str, "2147483647") <= 0;
}

exec_args_t *parse_cmdline_args(int argc, char *argv[])
{
    int c = 0;
    const struct option arguments[] = {
            {"file", required_argument, NULL, 'f'},
            {"ratio", required_argument, NULL, 'r'},
            {"help", no_argument, NULL, 'h'},
            {"log", required_argument, NULL, 'l'},
            {NULL, 0, NULL, 0}
    };
    static exec_args_t args = {
            .filepath = NULL,
            .ratio = 10
    };

    while ((c = getopt_long(argc, argv, "f:r:h" ,arguments, NULL)) != -1) {
        switch (c) {
            case 'f':
                args.filepath = malloc(sizeof(char) * strlen(args.filepath));
                if (!args.filepath) {
                    return NULL;
                }
                //strcpy(args.filepath, optarg);
                return NULL;
                break;
            case 'r':
                if (is_valid_number(optarg)) {
                    // TODO: strtol
                    args.ratio = atoi(optarg);
                    log_message(ERROR, "Invalid value for ratio argument");
                }
                break;
            case 'h':
                display_help();
                return NULL;
            case 'l':
                if (strlen(optarg))
                    set_log_filepath(optarg);
                break;
            default:
                return NULL;
        }
    }
    return args.filepath ? &args : NULL;
}