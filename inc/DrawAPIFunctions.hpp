//
// Created by Vadym KOZLOV on 8/24/18.
//

#ifndef NIBBLER_DRAWAPIFUNCTIONS_HPP
#define NIBBLER_DRAWAPIFUNCTIONS_HPP

#include <array>
#include <string>
#include "../drawAPI/inc/INibblerDisplay.hpp"
//using renderFunction		= void(*)(int type, float posX, float posY, float scale, float rot, std::array<float, 3> color);
//using initFunction			= void (*)(int , int , std::string const &);
//using preFrameFunction		= void (*)();
//using postFrameFunction		= void (*)();
//using processInputFunction	= const char* (*)(bool &);
//using deinitFunction		= void (*)();
//using textFunction			= void (*)(std::string, float, float, float, std::array<float, 3>);

using getApiFunction = INibblerDisplay*	(*)(int width, int height, const char *winName);


#endif //NIBBLER_DRAWAPIFUNCTIONS_HPP
