//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_SDL_HPP
#define NIBBLER_SDL_HPP

#include <string>
#include <array>
#include "drawer_sdl.hpp"
#include "INibblerDisplay.hpp"

extern "C" INibblerDisplay*			getDisplayModule(int width, int height, const char *winName);

class NibblerDisplaySDL : public INibblerDisplay
{
public:
	NibblerDisplaySDL(int width, int height, const char *winName);
	void preFrame() override;
	void postFrame() override;
	void			draw(int
			, float
			, float
			, float
			, float
			, std::array<float, 3>) override;
	void			putText(std::string what, float x, float y, float size, std::array<float, 3>) override;
	void			deinitializeApi() override;
	const char	*getInput(bool &) override;
private:
	Drawer mDrawer;
};

#endif
