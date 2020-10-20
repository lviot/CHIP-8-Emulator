/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** graphics.c
*/

#include <string.h>
#include "chip8.h"

graphics_t *init_graphics(int width, int height)
{
    graphics_t *graphics = NULL;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        return NULL;
    }

    graphics = malloc(sizeof(graphics_t));
    if (graphics == NULL) {
        return NULL;
    }

    graphics->window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN);
    if (graphics->window == NULL) {
        return NULL;
    }

    graphics->renderer = SDL_CreateRenderer(graphics->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (graphics->renderer == NULL) {
        return NULL;
    }

    memset(graphics->frame_buffer, 0, CHIP_WIDTH * CHIP_HEIGHT);
    graphics->render_flag = false;
    return graphics;
}

bool catch_quit_event(void)
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void clear_screen(void)
{
    chip8_t *chip = get_chip();

    SDL_SetRenderDrawColor(chip->graphics->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(chip->graphics->renderer);
}

/*
 * Actually doesn't draw a pixel, but a square
 * square size is deduced from screen size and ratio chosen
 */
void draw_pixel(ushort x, ushort y)
{
    chip8_t *chip = get_chip();

    SDL_Rect fillRect = {(x % CHIP_WIDTH) * RATIO, (y % CHIP_HEIGHT) * RATIO, 1 * RATIO, 1 * RATIO};
    SDL_SetRenderDrawColor(chip->graphics->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(chip->graphics->renderer, &fillRect);

}

void render(void)
{
    chip8_t *chip = get_chip();

    for (uint i = 0; i < CHIP_WIDTH * CHIP_HEIGHT; ++i) {
        if (chip->graphics->frame_buffer[i]) {
            draw_pixel(i % CHIP_WIDTH, i / CHIP_WIDTH);
        }
    }
    SDL_RenderPresent(chip->graphics->renderer);
    SDL_Delay(0);
}

void destroy_graphics(void)
{
    chip8_t *chip = get_chip();

    SDL_DestroyWindow(chip->graphics->window);
    SDL_DestroyRenderer(chip->graphics->renderer);
    SDL_Quit();
}