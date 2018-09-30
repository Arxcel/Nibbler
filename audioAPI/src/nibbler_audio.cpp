#include "nibbler_audio.hpp"
#include <iostream>

NibblerAudio::NibblerAudio()
{
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    mCollection.emplace_back(Mix_LoadMUS("/audioAPI/assets/snake.mp3"));
}

void NibblerAudio::playSound(int type, bool repeat)
{
    if (static_cast<size_t>(type) > mCollection.size())
        return;    
    Mix_AllocateChannels(1); 
    Mix_PlayMusic(mCollection.at(type), repeat ? -1 : 1);
}

void NibblerAudio::deinit()
{
    delete this;
}

NibblerAudio::~NibblerAudio()
{
    for (auto & m : mCollection)
        Mix_FreeMusic(m);
    SDL_Quit();
}

extern "C" INibblerAudio*   getAudioModule()
{
    return new NibblerAudio();
}