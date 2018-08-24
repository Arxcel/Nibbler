//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GLFW_HPP
#define NIBBLER_GLFW_HPP

#include "Drawer.hpp"
#include <string>
#include <array>

extern "C" void			initializeApi(int width, int height, std::string const &winName);
extern "C" const char	*getInput(bool &);
extern "C" void			deinitializeApi();
extern "C" void			draw(int
									, float
									, float
									, float
									, float
									, std::array<float, 3>);
extern "C" void			putText(std::string what, float x, float y, float size, std::array<float, 3>);
#endif
