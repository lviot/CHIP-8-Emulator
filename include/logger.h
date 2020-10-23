/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** logger.h
*/

#ifndef CHIP_8_LOGGER_H
#define CHIP_8_LOGGER_H

#define _DEBUG

#include <stdarg.h>

enum LOGGER_CODE {
    INFO,
    WARN,
    ERROR,
    FATAL,
};

typedef enum LOGGER_CODE CODE;

int log_message(CODE code, const char *format, ...);
void set_log_filepath(char *filepath);

#endif //CHIP_8_LOGGER_H
