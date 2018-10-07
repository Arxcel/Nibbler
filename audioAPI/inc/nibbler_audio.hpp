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
    void playSound(int type) override;
    void startMain() override;
    void stopMain() override;
    void deinit() override;

private:
    NibblerAudio(NibblerAudio const &);
    NibblerAudio &operator=(NibblerAudio const &);
    std::vector<Mix_Chunk *> mCollection;
    Mix_Music *mMainTheme;
 };

#endif
