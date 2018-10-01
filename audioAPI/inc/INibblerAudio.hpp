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
    virtual void startMain() = 0;
    virtual void stopMain() = 0;
    virtual void playSound(int type) = 0;
    virtual void deinit() = 0;
};

#endif //NIBBLER_GAME_INIBBLERDISPLAY_H
