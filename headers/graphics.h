/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** graphics.h
*/

#ifndef CHIP_8_GRAPHICS_H
#define CHIP_8_GRAPHICS_H

#include <stdbool.h>
#include <SDL.h>
#include "types.h"

#define RATIO           10
#define CHIP_WIDTH      64
#define CHIP_HEIGHT     32
#define WIN_WIDTH       CHIP_WIDTH * RATIO
#define WIN_HEIGHT      CHIP_HEIGHT * RATIO
#define FPS             1

struct graphics_s
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    uchar frame_buffer[CHIP_WIDTH * CHIP_HEIGHT];
    bool render_flag;
};

typedef struct graphics_s graphics_t;

graphics_t *init_graphics(int width, int height);
bool catch_quit_event(void);
void destroy_graphics(void);
void op_DXXX_pixel(ushort x, ushort y);
void clear_screen(void);
void render(void);
void op_DXXX_sprite(uchar x, uchar y, uchar mem_args);

#endif //CHIP_8_GRAPHICS_H