/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** audio.h
*/

#ifndef CHIP_8_AUDIO_H
#define CHIP_8_AUDIO_H

#include <SDL_audio.h>
#include <stdbool.h>

struct audio_s
{
    SDL_AudioDeviceID id;
    bool playing;
};

typedef struct audio_s audio_t;

void audio_callback(void* param, Uint8* stream, int len);
audio_t *init_audio(void);
void setAudioStatus(bool status);

#endif //CHIP_8_AUDIO_H
