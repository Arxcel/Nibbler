#include "nibbler_audio.hpp"
#include <iostream>
#include "CustomException.hpp"

NibblerAudio::NibblerAudio()
{
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        throw CustomException("Failed to init SDL");
    if (flags != (result = Mix_Init(flags)))
        throw CustomException("Could not initialize mixer.");
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    mMainTheme = Mix_LoadMUS("/audioAPI/assets/main_theme.mp3");
    mCollection.emplace_back(Mix_LoadWAV("/audioAPI/assets/speed.wav"));
    mCollection.emplace_back(Mix_LoadWAV("/audioAPI/assets/food.wav"));
    mCollection.emplace_back(Mix_LoadWAV("/audioAPI/assets/end.wav"));
}

void NibblerAudio::startMain() 
{
    Mix_PlayMusic(mMainTheme, -1);
}

void NibblerAudio::stopMain()
{
    Mix_HaltMusic();
}

void NibblerAudio::playSound(int type)
{
    if (static_cast<size_t>(type) > mCollection.size())
        return;
    Mix_PlayChannel(1, mCollection.at(type), 0);
}

void NibblerAudio::deinit()
{
    delete this;
}

NibblerAudio::~NibblerAudio()
{
    for (auto & m : mCollection)
        Mix_FreeChunk( m );
    Mix_FreeMusic(mMainTheme);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

NibblerAudio::NibblerAudio(NibblerAudio const &)
{

}

NibblerAudio &NibblerAudio::operator=(NibblerAudio const &)
{
    return *this;
}

extern "C" INibblerAudio*   getAudioModule()
{
    return new NibblerAudio();
}