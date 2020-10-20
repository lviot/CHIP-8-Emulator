/*
** EPITECH PROJECT, 2019
** CHIP_8
** File description:
** audio.c
*/

#include "chip8.h"
#include "audio.h"

void audio_callback(void *param, Uint8* stream, int len)
{
    size_t samples = len / sizeof(float);

    (void)param;
    for (size_t i = 0; i < samples; i++)
    {
        stream[i] = 0.5 * SDL_sinf((float)(2.0 * M_PI * i / 1000.0));
    }
}

void setAudioStatus(bool status)
{
    SDL_PauseAudioDevice(get_chip()->audio->id, !status ? SDL_TRUE : SDL_FALSE);
}

audio_t *init_audio(void)
{
    audio_t *audio = malloc(sizeof(struct audio_s));
    SDL_AudioSpec spec;

    if (!audio || SDL_Init(SDL_INIT_AUDIO) < 0)
        return NULL;

    SDL_memset(&spec, 0, sizeof(spec));

    spec.freq = 96000;
    spec.format = AUDIO_F32SYS;
    spec.channels = 1;
    spec.samples = 4096;
    spec.callback = audio_callback;

    audio->id = SDL_OpenAudioDevice(NULL, 0, &spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    audio->playing = false;

    SDL_PauseAudioDevice(audio->id, SDL_TRUE);

    return audio;
}

