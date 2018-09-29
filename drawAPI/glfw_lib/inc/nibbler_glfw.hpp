//
// Created by Vadym KOZLOV on 7/7/18.
//

#ifndef NIBBLER_GLFW_HPP
#define NIBBLER_GLFW_HPP

#include <string>
#include <array>
#include "drawer_glfw.hpp"
#include "INibblerDisplay.hpp"

extern "C" INibblerDisplay*			getDisplayModule(int width, int height, const char *winName);

class NibblerDisplayGLFW : public INibblerDisplay
{
public:
	NibblerDisplayGLFW(int width, int height, const char *winName);
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
