/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** logger.c
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logger.h"

static char *log_file_path = "log.txt";
FILE* log_stream = NULL;

static const char *formats[] = {
        [INFO] = "[%s] \033[0;34mInfo\033[0m: %s.\n",
        [WARN] = "[%s] \033[0;33mWarning\033[0m: %s.\n",
        [ERROR] = "[%s] \033[0;31mError\033[0m: %s.\n",
        [FATAL] = "[%s] \033[1;31mFatal\033[0m: %s. Quitting program...\n",
};

static char *str_time(void)
{
    time_t current_time;
    struct tm *time_info;
    char *str = malloc(sizeof(char) * 9);

    if (!str) {
        return NULL;
    }

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(str, 9, "%H:%M:%S", time_info);
    return str;
}

static char *build_log_message(CODE code, const char *format, va_list ap)
{
    char *message = NULL;
    char *line = NULL;
    char *time = str_time();

    if (!time) {
        return NULL;
    }
    
    if (vasprintf(&message, format, ap) == -1) {
        return NULL;
    }
    
    if (asprintf(&line, formats[code], time, message) == -1) {
        return NULL;
    }

    free(message);
    free(time);
    
    return line;
}

static void close_log_stream(void)
{
    if (log_stream)
        fclose(log_stream);
}

static int save_log_message(const char *message)
{
    static bool initialized = false;
    
    if (!initialized) {
        log_stream = fopen(log_file_path, "w");

        if (!log_stream) {
            return -1;
        }

        atexit(close_log_stream);
        initialized = true;
    }

    if (log_stream) {
        fwrite(message, strlen(message), 1, log_stream);
    }

    return 0;
}

void set_log_filepath(char *filepath)
{
    log_file_path = filepath;
}

int log_message(CODE code, const char *format, ...)
{
#ifndef _DEBUG
    return 0;
#endif
    char *line = NULL;
    va_list ap;


    va_start(ap, format);
    line = build_log_message(code, format, ap);
    va_end(ap);
    
    if (!line) {
        return -1;
    }

    fprintf(code == INFO ? stdout : stderr, "%s", line);
    save_log_message(line);
    free(line);
    return 0;
}