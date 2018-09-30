//
// Created by Vadym KOZLOV on 9/29/18.
//

#include <array>

#ifndef NIBBLER_GAME_INIBBLERAUDIO_H
#define NIBBLER_GAME_INIBBLERAUDIO_H
class INibblerAudio
{
public:
    virtual ~INibblerAudio() {};
    virtual void playSound(int type, bool repeat) = 0;
    virtual void deinit() = 0;
};

#endif //NIBBLER_GAME_INIBBLERDISPLAY_H
