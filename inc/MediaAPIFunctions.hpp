//
// Created by Vadym KOZLOV on 8/24/18.
//

#ifndef NIBBLER_MediaAPIFUNCTIONS_HPP
#define NIBBLER_MediaAPIFUNCTIONS_HPP

#include <array>
#include <string>
#include "../drawAPI/inc/INibblerDisplay.hpp"
#include "../audioAPI/inc/INibblerAudio.hpp"

using getDisplayApiFunction = INibblerDisplay*	(*)(int width, int height, const char *winName);
using getAudioApiFunction = INibblerAudio*	(*)();

#endif //NIBBLER_MediaAPIFUNCTIONS_HPP
