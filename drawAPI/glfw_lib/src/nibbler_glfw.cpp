//
// Created by Vadym KOZLOV on 7/7/18.
//

#include <vector>
#include "nibbler_glfw.hpp"

const std::vector<std::string> cTextures{ "block", "head", "body", "body_turn_left", "body_turn_right", "tail", "food"};

extern "C" INibblerDisplay*			getDisplayModule(int width, int height, const char *winName)
{
	return new NibblerDisplayGLFW(width, height, winName);
}


NibblerDisplayGLFW::NibblerDisplayGLFW(int width, int height, const char *winName): mDrawer(width, height, winName)
{
}

void NibblerDisplayGLFW::preFrame()
{
	mDrawer.preFrame();
}

void NibblerDisplayGLFW::postFrame()
{
	mDrawer.postFrame();
}

const char *NibblerDisplayGLFW::getInput(bool &isRunning)
{
	std::string cmd = mDrawer.processInput(isRunning);
	if (cmd != "nothing")
		return cmd.c_str();
	return nullptr;
}

void NibblerDisplayGLFW::deinitializeApi()
{
	delete this;
}

void NibblerDisplayGLFW::draw(int type
		, float posX, float posY
		, float scale
		, float rot
		, std::array<float, 3> color)
{
	if (static_cast<size_t>(type) > cTextures.size())
		type = 0;
	mDrawer.draw(cTextures[type], {posX, posY}, {scale, scale}, static_cast<float>(rot * M_PI / 180.0f), {color[0], color[1], color[2]});
}

void			NibblerDisplayGLFW::putText(std::string what, float x, float y, float size, std::array<float, 3> color)
{
	mDrawer.putString(what, {x, y}, size, {color[0], color[1], color[2]});
}

