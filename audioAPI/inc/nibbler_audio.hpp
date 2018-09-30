//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_AUDIO_HPP
#define NIBBLER_AUDIO_HPP

#include <string>
#include <array>
#include "INibblerAudio.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include <vector>

extern "C" INibblerAudio*   getAudioModule();

class NibblerAudio : public INibblerAudio
{
public:
	NibblerAudio();
    ~NibblerAudio();
    void playSound(int type, bool repeat) override;
    void deinit() override;

private:
    std::vector<Mix_Music *> mCollection;
};

#endif
