/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** keyboard.c
*/

#include "keyboard.h"

SDL_Scancode get_scancode(uchar key)
{
    static SDL_Keycode key_map[] = {
            [0x0] = SDL_SCANCODE_0,
            [0x1] = SDL_SCANCODE_1,
            [0x2] = SDL_SCANCODE_2,
            [0x3] = SDL_SCANCODE_3,
            [0x4] = SDL_SCANCODE_4,
            [0x5] = SDL_SCANCODE_5,
            [0x6] = SDL_SCANCODE_6,
            [0x7] = SDL_SCANCODE_7,
            [0x8] = SDL_SCANCODE_8,
            [0x9] = SDL_SCANCODE_9,
            [0xA] = SDL_SCANCODE_A,
            [0xB] = SDL_SCANCODE_B,
            [0xC] = SDL_SCANCODE_C,
            [0xD] = SDL_SCANCODE_D,
            [0xE] = SDL_SCANCODE_E,
            [0xF] = SDL_SCANCODE_F,
    };

    return key_map[key];
}

void get_keys_states(void)
{
    chip8_t *chip = get_chip();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    for (uint i = 0; i < KEY_NB; ++i) {
        chip->keys[i] = state[get_scancode(i)];
    }
}

bool is_op_EXXX(uchar key)
{
    return get_chip()->keys[key];
}

uchar wait_for_keypress(void)
{
    static uchar key_map[] = {
            [SDL_SCANCODE_0] = 0x0,
            [SDL_SCANCODE_1] = 0x1,
            [SDL_SCANCODE_2] = 0x2,
            [SDL_SCANCODE_3] = 0x3,
            [SDL_SCANCODE_4] = 0x4,
            [SDL_SCANCODE_5] = 0x5,
            [SDL_SCANCODE_6] = 0x6,
            [SDL_SCANCODE_7] = 0x7,
            [SDL_SCANCODE_8] = 0x8,
            [SDL_SCANCODE_9] = 0x9,
            [SDL_SCANCODE_A] = 0xA,
            [SDL_SCANCODE_B] = 0xB,
            [SDL_SCANCODE_C] = 0xC,
            [SDL_SCANCODE_D] = 0xD,
            [SDL_SCANCODE_E] = 0xE,
            [SDL_SCANCODE_F] = 0xF,
    };
    SDL_Event e;

    while (true) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_KEYDOWN) {
            return key_map[e.key.keysym.scancode];
        }
    }
}
